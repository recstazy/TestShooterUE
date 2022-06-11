#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestShooter/HealthSystem/HealthSystem.h"
#include "TestShooterGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerSpawnedSignature, AActor*, playerActor);

UCLASS(minimalapi)
class ATestShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestShooterGameMode();
	virtual void RestartPlayer(AController* NewPlayer) override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnPlayerSpawnedSignature OnPlayerSpawned;

private:
	UFUNCTION()
	void PlayerDead(UHealthSystem* health);
};



