#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TestShooter/Weapon/IWeapon.h"
#include "IWeaponController.generated.h"

UINTERFACE()
class UWeaponController : public UInterface
{
	GENERATED_BODY()
};

class TESTSHOOTER_API IWeaponController
{
	GENERATED_BODY()
	
public:
	virtual IWeapon* GetWeapon() = 0;
	
	UFUNCTION()
	virtual void Attached(UObject* toObject) = 0;
	
	UFUNCTION()
	virtual void TriggerDown() = 0;

	UFUNCTION()
	virtual void TriggerUp() = 0;

	UFUNCTION()
	virtual void Reload() = 0;
};
