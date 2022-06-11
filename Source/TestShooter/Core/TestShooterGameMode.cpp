#include "TestShooterGameMode.h"
#include "TestShooterCharacter.h"
#include "TestShooter/UI/TestShooterHUD.h"

ATestShooterGameMode::ATestShooterGameMode()
	: Super()
{
	DefaultPawnClass = ATestShooterCharacter::StaticClass();
	HUDClass = ATestShooterHUD::StaticClass();
}

void ATestShooterGameMode::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);

	const auto pawn = NewPlayer->GetPawn();
	OnPlayerSpawned.Broadcast(pawn);
	const auto healthOwner = Cast<IHealthOwner>(pawn);
	const auto health = healthOwner->GetHealthSystem();
	health->OnDeath.AddDynamic(this, &ATestShooterGameMode::PlayerDead);
}

void ATestShooterGameMode::PlayerDead(UHealthSystem* health)
{
	auto pawn = Cast<APawn>(health->GetOwner());
	auto controller = pawn->GetController();
	pawn->Destroy();
	RestartPlayer(controller);
}
