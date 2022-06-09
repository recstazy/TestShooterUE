#pragma once

#include "CoreMinimal.h"
#include "IWeaponController.h"
#include "GameFramework/Actor.h"
#include "TestShooter/Collectable/ICollectable.h"
#include "WeaponActor.generated.h"

UCLASS()
class TESTSHOOTER_API AWeaponActor : public AActor, public ICollectable
{
	GENERATED_BODY()

public:
	AWeaponActor();

	UFUNCTION(BlueprintCallable)
	virtual void OnCollected(UObject* collectedObject) override;

	IWeaponController* GetWeaponController() const;
	
	UFUNCTION(BlueprintCallable)
	void GetWeaponControllerBP(TScriptInterface<IWeaponController>& outController) const;

protected:
	virtual void BeginPlay() override;

private:
	IWeaponController* WeaponController;
};
