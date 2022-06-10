#include "AmmoContainer.h"

UAmmoContainer::UAmmoContainer()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UAmmoContainer::TryAddAmmo(int amount)
{
	const int resultCurrentAmmo  = FMath::Min(CurrentAmmo + amount, MaxAmmo);
	const bool canAddAny = resultCurrentAmmo - CurrentAmmo > 0;

	if (!canAddAny)
		return false;
	
	CurrentAmmo = resultCurrentAmmo;
	OnAmmoChanged.Broadcast(CurrentAmmo);
	return true;
}

int UAmmoContainer::DrainAmmo(int expectedAmount)
{
	const int resultCurrentAmmo  = FMath::Max(CurrentAmmo - expectedAmount, 0);
	const int drainedAmount = CurrentAmmo - resultCurrentAmmo;
	CurrentAmmo = resultCurrentAmmo;

	OnAmmoChanged.Broadcast(CurrentAmmo);
	return drainedAmount;
}

int UAmmoContainer::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

