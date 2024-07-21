// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "HighResScreenshot.h"
#include "GameFramework/PlayerController.h"
#include "ImageUtils.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	TArray<FRotator> eulerAngles;
	eulerAngles.Add(FRotator(0.0f, 0.0f, 0.0f));
	eulerAngles.Add(FRotator(0.0f, 0.0f, -90.0f));
	eulerAngles.Add(FRotator(0.0f, 0.0f, 90.0f));
	eulerAngles.Add(FRotator(0.0f, 0.0f, 180.0f));
	eulerAngles.Add(FRotator(-90.0f, 0.0f, 0.0f));
	eulerAngles.Add(FRotator(90.0f, 0.0f, 0.0f));

	if (CameraActors.Num() > 0)
	{
		for (int i = 0; i < 6; ++i)
		{
			ACameraActor* CameraActor = Cast<ACameraActor>(CameraActors[0]);
			FRotator currentAngle = eulerAngles[i];
			CameraActor->SetActorRotation(currentAngle);

			PlayerController->SetViewTarget(CameraActor);

			FString ScreenshotName = TEXT("MyScreenshot");
			GScreenshotResolutionX = 2048;
			GScreenshotResolutionY = 2048;
			GetHighResScreenshotConfig().FilenameOverride = ScreenshotName;
			GEngine->GameViewport->Viewport->TakeHighResScreenShot();
			PlayerController->SetViewTarget(nullptr);
		}
	}
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

