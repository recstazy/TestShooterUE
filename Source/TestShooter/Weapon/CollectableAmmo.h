#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TestShooter/Collectable/Collectable.h"
#include "CollectableAmmo.generated.h"

UCLASS()
class TESTSHOOTER_API ACollectableAmmo : public AActor, public ICollectable
{
	GENERATED_BODY()

public:
	ACollectableAmmo();

	UFUNCTION(BlueprintCallable)
	virtual void OnCollected(UObject* collectedObject) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* Sphere;

private:
	UPROPERTY(EditDefaultsOnly)
	int AmmoAmount;
};
