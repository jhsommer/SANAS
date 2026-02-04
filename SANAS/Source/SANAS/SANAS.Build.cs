// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SANAS : ModuleRules
{
	public SANAS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayTags", "UMG" });
	}
}
