// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class LootTheDungeon : ModuleRules
{
	public LootTheDungeon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivateIncludePaths.Add(EnginePath + "Source/Runtime/Online/Voice/Private");
        PrivateIncludePaths.Add(EnginePath + "Source/Runtime/Online/Voice/Private/Windows");
        PrivateDependencyModuleNames.AddRange(new string[]{
	    //...
	    "AudioCapture",
        "AudioMixer",
        "Voice",
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }

}
