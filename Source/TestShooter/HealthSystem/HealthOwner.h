#pragma once

#include "CoreMinimal.h"
#include "HealthSystem.h"
#include "UObject/Interface.h"
#include "HealthOwner.generated.h"

UINTERFACE()
class UHealthOwner : public UInterface
{
	GENERATED_BODY()
};

class TESTSHOOTER_API IHealthOwner
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual UHealthSystem* GetHealthSystem() = 0;
};
