// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SlimeHotel : ModuleRules
{
	public SlimeHotel(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
