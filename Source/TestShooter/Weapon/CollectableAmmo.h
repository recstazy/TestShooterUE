#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestShooter/Collectable/Collectable.h"
#include "CollectableAmmo.generated.h"

UCLASS()
class TESTSHOOTER_API ACollectableAmmo : public AActor, public ICollectable
{
	GENERATED_BODY()

public:
	ACollectableAmmo();
	virtual void OnCollected() override;
};
