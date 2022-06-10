#pragma once

#include "CoreMinimal.h"
#include "AmmoContainer.h"
#include "Components/ActorComponent.h"
#include "WeaponClip.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClipAmmoChangedSignature, int, currentValue);

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

	UFUNCTION(BlueprintCallable)
	int GetCurrentAmmo() const;

public:
	UPROPERTY(BlueprintAssignable)
	FClipAmmoChangedSignature OnCurrentAmmoChanged;

private:
	UPROPERTY(EditDefaultsOnly)
	int MaxAmmo;

	UPROPERTY(VisibleAnywhere)
	int CurrentAmmo;

protected:
	virtual void BeginPlay() override;
};
