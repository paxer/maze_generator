// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Maze : ModuleRules
{
	public Maze(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UnrealEd"});
	}
}
