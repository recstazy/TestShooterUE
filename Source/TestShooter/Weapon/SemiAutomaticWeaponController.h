#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponController.h"
#include "SemiAutomaticWeaponController.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API USemiAutomaticWeaponController : public UBaseWeaponController
{
	GENERATED_BODY()

public:
	USemiAutomaticWeaponController();
	virtual void TriggerDown() override;
};
