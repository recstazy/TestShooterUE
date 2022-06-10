#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AmmoContainer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FContainerAmmoChangedSignature, int, amount);

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

	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmo() const;

public:
	UPROPERTY(EditDefaultsOnly)
	int MaxAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentAmmo;

	UPROPERTY(BlueprintAssignable)
	FContainerAmmoChangedSignature OnAmmoChanged;
};
