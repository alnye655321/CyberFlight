// Copyright 2020 NyeDigital

using UnrealBuildTool;
using System.Collections.Generic;

public class CyberFlightEditorTarget : TargetRules
{
	public CyberFlightEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "CyberFlight" } );
	}
}
