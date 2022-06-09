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

protected:
	virtual void BeginPlay() override;
	virtual void Attached(UObject* toObject) override;
	virtual void Reload() override;
	virtual void TriggerDown() override;
	virtual void TriggerUp() override;

protected:
	IWeapon* Weapon;
	IAmmoContainerOwner* AmmoOwner;

	UPROPERTY()
	UWeaponClip* Clip;
};
