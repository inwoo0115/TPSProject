// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TPSProject : ModuleRules
{
	public TPSProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// ������Ʈ ��� �߰�
		PublicIncludePaths.Add("TPSProject");

		// ���̺� ������Ʈ ��� �߰�
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CableComponent", "UMG", "OnlineSubsystem", "OnlineSubsystemUtils", "CableComponent", "Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
