#pragma once

#include "CoreMinimal.h"
#include "HeldWeaponChangeNotifier.h"
#include "UObject/Interface.h"
#include "WeaponActor.h"
#include "IWeaponHolder.generated.h"

UINTERFACE()
class UWeaponHolder : public UInterface
{
	GENERATED_BODY()
};

class TESTSHOOTER_API IWeaponHolder
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void PickUpWeapon(AWeaponActor* weaponActor) = 0;

	UFUNCTION()
	virtual AWeaponActor* GetWeapon() const = 0;

	UFUNCTION()
	virtual UHeldWeaponChangeNotifier* GetHeldWeaponChangedNotifier() const = 0;
};
