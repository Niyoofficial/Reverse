// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VDownEditorTarget : TargetRules
{
	public VDownEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		bAllowHotReload = false;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "VDown" } );
	}
}
