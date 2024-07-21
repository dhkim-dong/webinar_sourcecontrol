#include "Capture.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "HighResScreenshot.h"
#include "Runtime/ImageWrapper/Public/Interfaces/IImageWrapper.h"
#include "Runtime/Engine/Public/HighResScreenshot.h"
#include "ImageUtils.h"
#include "FileHelper.h"
#include "Paths.h"

UTextureRenderTarget2D* ACapture::CreateRenderTarget2D(int32 width, int32 height, bool makeHDR)
{
	UTextureRenderTarget2D* renderTarget = NewObject<UTextureRenderTarget2D>();

	if (makeHDR)
		renderTarget->InitAutoFormat(width, height);
	else
		renderTarget->InitCustomFormat(width, height, PF_B8G8R8A8, false);

	return renderTarget;
}

bool ACapture::SaveRenderTarget(UTextureRenderTarget2D* renderTarget, FString path, FString fileName)
{
	FTextureRenderTargetResource* resource = renderTarget->GameThread_GetRenderTargetResource();
	FReadSurfaceDataFlags readPixelFlags(RCM_UNorm);

	TArray<FColor> outBMP;
	outBMP.AddUninitialized(renderTarget->GetSurfaceWidth() * renderTarget->GetSurfaceHeight());
	resource->ReadPixels(outBMP, readPixelFlags);

	for (FColor& color : outBMP)
	{
		color.A = 255;
	}

	FIntPoint destSize(renderTarget->GetSurfaceWidth(), renderTarget->GetSurfaceHeight());
	TArray<uint8> compressedBitmap;
	FImageUtils::CompressImageArray(destSize.X, destSize.Y, outBMP, compressedBitmap);

	FString fullPath = FPaths::Combine(path, fileName);

	bool imageSavedOK = FFileHelper::SaveArrayToFile(compressedBitmap, *fullPath);

	return imageSavedOK;
}

