// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MapCaptureStyle.h"

class FMapCaptureCommands : public TCommands<FMapCaptureCommands>
{
public:

	FMapCaptureCommands()
		: TCommands<FMapCaptureCommands>(TEXT("MapCapture"), NSLOCTEXT("Contexts", "MapCapture", "MapCapture Plugin"), NAME_None, FMapCaptureStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
