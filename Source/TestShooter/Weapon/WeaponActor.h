#pragma once

#include "CoreMinimal.h"
#include "IWeaponController.h"
#include "WeaponClip.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TestShooter/Collectable/ICollectable.h"
#include "WeaponActor.generated.h"

UCLASS()
class TESTSHOOTER_API AWeaponActor : public AActor, public ICollectable
{
	GENERATED_BODY()

public:
	AWeaponActor();
	IWeaponController* GetWeaponController() const;

	UFUNCTION(BlueprintCallable)
	void OverrideShootOrigin(USceneComponent* inOrigin);

	UFUNCTION(BlueprintCallable)
	virtual void OnCollected(UObject* collectedObject) override;

	UFUNCTION(BlueprintCallable)
	void GetWeaponControllerBP(TScriptInterface<IWeaponController>& outController) const;

protected:
	virtual void BeginPlay() override;

private:
	IWeaponController* WeaponController;

	UPROPERTY(VisibleAnywhere)
	UWeaponClip* Clip;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* CollectableTrigger;
};
