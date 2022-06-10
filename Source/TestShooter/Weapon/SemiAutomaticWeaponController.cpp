#include "SemiAutomaticWeaponController.h"

USemiAutomaticWeaponController::USemiAutomaticWeaponController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USemiAutomaticWeaponController::TriggerDown()
{
	if (Weapon == nullptr)
		return;

	if (Clip->TrySpend(1))
		Weapon->MakeOneShot();
}

void USemiAutomaticWeaponController::TriggerUp()
{
}

