#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoContainer.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API UAmmoContainer : public UActorComponent
{
	GENERATED_BODY()

public:
	UAmmoContainer();

	UFUNCTION(BlueprintCallable)
	bool TryAddAmmo(int amount);

	UFUNCTION(BlueprintCallable)
	int DrainAmmo(int expectedAmount);

public:
	UPROPERTY(EditDefaultsOnly)
	int MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentAmmo;
};
