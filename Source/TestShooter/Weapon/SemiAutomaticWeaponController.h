#pragma once

#include "CoreMinimal.h"
#include "AmmoContainer.h"
#include "IAmmoContainerOwner.h"
#include "IWeapon.h"
#include "IWeaponController.h"
#include "WeaponClip.h"
#include "Components/ActorComponent.h"
#include "SemiAutomaticWeaponController.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API USemiAutomaticWeaponController : public UActorComponent, public IWeaponController
{
	GENERATED_BODY()

public:
	USemiAutomaticWeaponController();
	virtual void Attached(UObject* toObject) override;
	virtual void TriggerDown() override;
	virtual void TriggerUp() override;
	virtual void Reload() override;

protected:
	virtual void BeginPlay() override;

private:
	IWeapon* Weapon;
	IAmmoContainerOwner* AmmoOwner;

	UPROPERTY()
	UWeaponClip* Clip;
};
