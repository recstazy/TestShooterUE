#include "SemiAutomaticWeaponController.h"

USemiAutomaticWeaponController::USemiAutomaticWeaponController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USemiAutomaticWeaponController::TriggerDown()
{
	if (Weapon == nullptr)
		return;

	Weapon->MakeOneShot();
}

void USemiAutomaticWeaponController::TriggerUp()
{
}

