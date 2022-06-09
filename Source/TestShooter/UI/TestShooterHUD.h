// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "TestShooterHUD.generated.h"

UCLASS()
class TESTSHOOTER_API ATestShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATestShooterHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

public:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> AmmoWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UUserWidget> HealthWidgetClass;

private:
	void DrawCrosshair();
	
private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};

