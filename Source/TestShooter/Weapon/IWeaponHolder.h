#pragma once

#include "CoreMinimal.h"
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
	virtual void PickUpWeapon(AWeaponActor* weaponActor) = 0;
};
