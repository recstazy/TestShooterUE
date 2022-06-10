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

	Timer = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(
		Timer, this, &UAutomaticWeaponController::TimerFireCallback, 1.0f/FireRatePerSecond, true);
}

void UAutomaticWeaponController::TriggerUp()
{
	GetWorld()->GetTimerManager().ClearTimer(Timer);
	Timer.Invalidate();
}

void UAutomaticWeaponController::TimerFireCallback()
{
	if (Weapon == nullptr)
		return;
	
	if (Clip->TrySpend(1))
		Weapon->MakeOneShot();
}

