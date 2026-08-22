// How to change Input Audio Device in Unreal Engine 5 without engine modification (Windows only)
// Tested with UE5.5 editor and shipping

// in your widget:

#include "AudioCapture.h"
#include "AudioCaptureBlueprintLibrary.h"
#include "Net/VoiceConfig.h"
#include "VoiceInterfaceImpl.h"
#include "VoiceEngineImpl.h"
#include "OnlineSubsystemUtils.h"
#include "Interfaces/VoiceCapture.h"
#include "VoiceCaptureWindows.h"

struct FOnlineVoiceImplEx : public FOnlineVoiceImpl
{
	IVoiceEnginePtr GetVoiceEngine() const
	{
		return VoiceEngine;
	}
};

struct FVoiceEngineImplEx : public FVoiceEngineImpl
{
	TSharedPtr<IVoiceCapture> GetVoiceCapture_Public() const
	{
		return GetVoiceCapture();
	}
};

FVoiceCaptureWindows* GetWinVoiceCapture(UWorld* World)
{
	IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface(World);
	if (VoiceInterface)
	{
		if (IVoiceEnginePtr VoiceEngine = ((FOnlineVoiceImplEx*)VoiceInterface.Get())->GetVoiceEngine())
		{
			if (auto VoiceCapture = ((FVoiceEngineImplEx*)VoiceEngine.Get())->GetVoiceCapture_Public())
			{
				return ((FVoiceCaptureWindows*)VoiceCapture.Get());
			}
		}
	}

	return nullptr;
}

float UAudioSettingsWidget::GetVoiceLevel() const
{
	if (auto VoiceCapture = GetWinVoiceCapture(GetWorld()))
	{
		return VoiceCapture->GetCurrentAmplitude();
	}

	return 0.f;
}

void UAudioSettingsWidget::OnAudioDeviceChanged(FString DeviceName, ESelectInfo::Type SelectionType)
{
	IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface(GetWorld());

	if (ensure(VoiceInterface.IsValid()))
	{
		VoiceInterface->StopNetworkedVoice(/*LocalPlayerNum*/0);
	}

	verify(VoiceCapture->ChangeDevice(DeviceName, UVOIPStatics::GetVoiceSampleRate(), UVOIPStatics::GetVoiceNumChannels()));

	ApplyVoiceSettings(); // this call StartNetworkedVoice if needed
}