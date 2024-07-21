// Copyright Epic Games, Inc. All Rights Reserved.

#include "MapCapture.h"
#include "MapCaptureStyle.h"
#include "MapCaptureCommands.h"
#include "Misc/MessageDialog.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "ToolMenus.h"
#include <Kismet/GameplayStatics.h>

static const FName MapCaptureTabName("MapCapture");

#define LOCTEXT_NAMESPACE "FMapCaptureModule"

void FMapCaptureModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FMapCaptureStyle::Initialize();
	FMapCaptureStyle::ReloadTextures();

	FMapCaptureCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMapCaptureCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FMapCaptureModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMapCaptureModule::RegisterMenus));
}

void FMapCaptureModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMapCaptureStyle::Shutdown();

	FMapCaptureCommands::Unregister();
}

void FMapCaptureModule::PluginButtonClicked()
{
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GEditor->GetWorld(), ACameraActor::StaticClass(), CameraActors);


	if (CameraActors.Num() > 0)
	{
		ACameraActor* CameraActor = Cast<ACameraActor>(CameraActors[0]);
		UE_LOG(LogTemp, Warning, TEXT("Count"));
	}
}

void FMapCaptureModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FMapCaptureCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FMapCaptureCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMapCaptureModule, MapCapture)