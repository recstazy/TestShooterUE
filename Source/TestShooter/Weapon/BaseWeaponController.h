#pragma once

#include "CoreMinimal.h"
#include "IAmmoContainerOwner.h"
#include "IWeapon.h"
#include "IWeaponController.h"
#include "WeaponClip.h"
#include "Components/ActorComponent.h"
#include "BaseWeaponController.generated.h"

UCLASS(ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API UBaseWeaponController : public UActorComponent, public IWeaponController
{
	GENERATED_BODY()

public:
	UBaseWeaponController();
	IAmmoContainerOwner* GetAmmoOwner() const;

	UFUNCTION(BlueprintCallable)
	UWeaponClip* GetClip() const;

protected:
	virtual void BeginPlay() override;
	virtual IWeapon* GetWeapon() override;

	UFUNCTION()
	virtual void Attached(UObject* toObject) override;

	UFUNCTION(BlueprintCallable)
	virtual void Reload() override;

	UFUNCTION(BlueprintCallable)
	virtual void TriggerDown() override;

	UFUNCTION(BlueprintCallable)
	virtual void TriggerUp() override;

protected:
	IWeapon* Weapon;
	IAmmoContainerOwner* AmmoOwner;

	UPROPERTY(VisibleAnywhere)
	UWeaponClip* Clip;
};
