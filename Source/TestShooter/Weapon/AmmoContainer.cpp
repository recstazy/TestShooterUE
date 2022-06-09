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

	const auto message = FString::Printf(TEXT("Current Ammo: %d"), CurrentAmmo);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
	return true;
}

int UAmmoContainer::DrainAmmo(int expectedAmount)
{
	const int resultCurrentAmmo  = FMath::Max(CurrentAmmo - expectedAmount, 0);
	const int drainedAmount = CurrentAmmo - resultCurrentAmmo;
	CurrentAmmo = resultCurrentAmmo;

	const auto message = FString::Printf(TEXT("Ammo Drained: %d"), drainedAmount);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
	return  drainedAmount;
}

