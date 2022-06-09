#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IWeapon.generated.h"

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
	virtual void MakeOneShot() = 0;
};
