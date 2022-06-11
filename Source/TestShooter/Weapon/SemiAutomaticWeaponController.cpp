#include "SemiAutomaticWeaponController.h"

USemiAutomaticWeaponController::USemiAutomaticWeaponController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USemiAutomaticWeaponController::TriggerDown()
{
	MakeOneShot();
}

