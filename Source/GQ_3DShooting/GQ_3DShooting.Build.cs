// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GQ_3DShooting : ModuleRules
{
	public GQ_3DShooting(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
