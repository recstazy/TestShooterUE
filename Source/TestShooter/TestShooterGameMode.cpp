// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestShooterGameMode.h"
#include "TestShooterHUD.h"
#include "TestShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestShooterGameMode::ATestShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestShooterHUD::StaticClass();
}
