#include "WeaponClip.h"

UWeaponClip::UWeaponClip()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponClip::Reload(UAmmoContainer* container)
{
	CurrentAmmo += container->DrainAmmo(MaxAmmo);
	OnCurrentAmmoChanged.Broadcast(CurrentAmmo);
}

bool UWeaponClip::TrySpend(int ammoAmount)
{
	const int resultAmmo = CurrentAmmo - ammoAmount;
	if (resultAmmo < 0)
		return false;
	
	CurrentAmmo = resultAmmo;
	OnCurrentAmmoChanged.Broadcast(CurrentAmmo);
	return true;
}

int UWeaponClip::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

void UWeaponClip::BeginPlay()
{
	CurrentAmmo = MaxAmmo;
	Super::BeginPlay();
}

