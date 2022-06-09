#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TestShooter/Collectable/ICollectable.h"
#include "CollectableHealth.generated.h"

UCLASS()
class TESTSHOOTER_API ACollectableHealth : public AActor, public  ICollectable
{
	GENERATED_BODY()

public:
	ACollectableHealth();

	UFUNCTION(BlueprintCallable)
	virtual void OnCollected(UObject* collectedObject) override;

public:
	UPROPERTY(EditDefaultsOnly)
	float HealthAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;
};
