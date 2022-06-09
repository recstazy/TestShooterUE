#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TestShooter/Collectable/Collectable.h"
#include "CollectableHealth.generated.h"

UCLASS()
class TESTSHOOTER_API ACollectableHealth : public AActor, public  ICollectable
{
	GENERATED_BODY()

public:
	ACollectableHealth();

	UFUNCTION(BlueprintCallable)
	virtual void OnCollected(AActor* collectedActor) override;

public:
	UPROPERTY(EditDefaultsOnly)
	float HealthAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;
};
