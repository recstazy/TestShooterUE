#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Weapon.generated.h"

UINTERFACE()
class UWeapon : public UInterface
{
	GENERATED_BODY()
};

class TESTSHOOTER_API IWeapon
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void Shoot() = 0;

	UFUNCTION()
	virtual void Reload() = 0;
};
