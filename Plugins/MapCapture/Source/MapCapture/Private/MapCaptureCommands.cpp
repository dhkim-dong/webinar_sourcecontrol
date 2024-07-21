// Copyright Epic Games, Inc. All Rights Reserved.

#include "MapCaptureCommands.h"

#define LOCTEXT_NAMESPACE "FMapCaptureModule"

void FMapCaptureCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "MapCapture", "Execute MapCapture action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
