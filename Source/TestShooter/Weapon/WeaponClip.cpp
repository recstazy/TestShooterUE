#include "WeaponClip.h"

UWeaponClip::UWeaponClip()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponClip::Reload(UAmmoContainer* container)
{
	CurrentAmmo += container->DrainAmmo(MaxAmmo);
}

bool UWeaponClip::TrySpend(int ammoAmount)
{
	const int resultAmmo = CurrentAmmo - ammoAmount;
	if (resultAmmo < 0)
		return false;
	
	CurrentAmmo = resultAmmo;
	return true;
}

void UWeaponClip::BeginPlay()
{
	CurrentAmmo = MaxAmmo;
	Super::BeginPlay();
}

