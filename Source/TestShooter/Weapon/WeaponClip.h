#pragma once

#include "CoreMinimal.h"
#include "AmmoContainer.h"
#include "Components/ActorComponent.h"
#include "WeaponClip.generated.h"

UCLASS(ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API UWeaponClip : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponClip();

	UFUNCTION(BlueprintCallable)
	void Reload(UAmmoContainer* container);

	UFUNCTION(BlueprintCallable)
	bool TrySpend(int ammoAmount);

private:
	UPROPERTY(EditDefaultsOnly)
	int MaxAmmo;

	UPROPERTY(VisibleAnywhere)
	int CurrentAmmo;

protected:
	virtual void BeginPlay() override;
};
