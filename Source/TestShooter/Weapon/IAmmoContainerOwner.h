#pragma once

#include "CoreMinimal.h"
#include "AmmoContainer.h"
#include "UObject/Interface.h"
#include "IAmmoContainerOwner.generated.h"

UINTERFACE()
class UAmmoContainerOwner : public UInterface
{
	GENERATED_BODY()
};

class TESTSHOOTER_API IAmmoContainerOwner
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual UAmmoContainer* GetAmmoContainer() = 0;
};
