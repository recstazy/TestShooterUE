#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Collectable.generated.h"

UINTERFACE()
class UCollectable : public UInterface
{
	GENERATED_BODY()
};

class TESTSHOOTER_API ICollectable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnCollected(AActor* collectedActor) = 0;
};
