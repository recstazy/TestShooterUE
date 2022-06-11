#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponController.h"
#include "AutomaticWeaponController.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API UAutomaticWeaponController : public UBaseWeaponController
{
	GENERATED_BODY()

public:
	UAutomaticWeaponController();
	virtual void TriggerDown() override;
	virtual void TriggerUp() override;

private:
	UPROPERTY(EditDefaultsOnly, meta=(ClampMin=0))
	float FireRatePerSecond;
	
	UPROPERTY()
	FTimerHandle Timer;
};
