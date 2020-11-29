// Copyright 2020 NyeDigital

using UnrealBuildTool;
using System.Collections.Generic;

public class CyberFlightTarget : TargetRules
{
	public CyberFlightTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "CyberFlight" } );
	}
}
