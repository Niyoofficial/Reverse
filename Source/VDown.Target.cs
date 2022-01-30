// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VDownTarget : TargetRules
{
	public VDownTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		bAllowLTCG = true;
		bAllowHotReload = false;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "VDown" } );
	}
}
