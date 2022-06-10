// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestShooterHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

ATestShooterHUD::ATestShooterHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/FirstPerson/Textures/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
}

void ATestShooterHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrosshair();
}

void ATestShooterHUD::BeginPlay()
{
	if (AmmoWidgetClass != nullptr)
	{
		AmmoWidget = CreateWidget(GetWorld(), AmmoWidgetClass);
		AmmoWidget->AddToPlayerScreen();
	}

	if (HealthWidgetClass != nullptr)
	{
		HealthWidget = CreateWidget(GetWorld(), HealthWidgetClass);
		HealthWidget->AddToPlayerScreen();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Add Health Widget"));
	}
	
	Super::BeginPlay();
}

void ATestShooterHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (HealthWidget != nullptr)
	{
		HealthWidget->RemoveFromParent();
		HealthWidget = nullptr;
	}

	if (AmmoWidget != nullptr)
	{
		AmmoWidget->RemoveFromParent();
		AmmoWidget = nullptr;
	}
	
	Super::EndPlay(EndPlayReason);
}

void ATestShooterHUD::DrawCrosshair()
{
	// Draw very simple crosshair

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	// offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition( (Center.X),
										   (Center.Y + 20.0f));

	// draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );
}
