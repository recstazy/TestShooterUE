#include "AutomaticWeaponController.h"

UAutomaticWeaponController::UAutomaticWeaponController()
{
	PrimaryComponentTick.bCanEverTick = true;
	FireRatePerSecond = 5.0f;
}

void UAutomaticWeaponController::TriggerDown()
{
	if (Weapon == nullptr)
		return;

	MakeOneShot();
	const float fireDelay = 1.0f/FireRatePerSecond;
	Timer = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(
		Timer, this, &UAutomaticWeaponController::MakeOneShot, fireDelay, true, fireDelay);
}

void UAutomaticWeaponController::TriggerUp()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	Timer.Invalidate();
}

