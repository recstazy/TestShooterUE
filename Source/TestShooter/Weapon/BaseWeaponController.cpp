#include "BaseWeaponController.h"

UBaseWeaponController::UBaseWeaponController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UWeaponClip* UBaseWeaponController::GetClip() const
{
	return Clip;
}

IAmmoContainerOwner* UBaseWeaponController::GetAmmoOwner() const
{
	return AmmoOwner;
}

void UBaseWeaponController::BeginPlay()
{
	Clip = Cast<UWeaponClip>(GetOwner()->GetComponentByClass(UWeaponClip::StaticClass()));
	if (Clip == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Clip not found on weapon"));

	const auto weaponComponents = GetOwner()->GetComponentsByInterface(UWeapon::StaticClass());

	if (weaponComponents.Num() > 0)
		Weapon = Cast<IWeapon>(weaponComponents[0]);
	else
		UE_LOG(LogTemp, Error, TEXT("Weapon component not found in Weapon"));
	
	ActivateOnShot = GetOwner()->GetComponentsByTag(UActorComponent::StaticClass(), ActivateOnShotComponentTag);
	Super::BeginPlay();
}

void UBaseWeaponController::Attached(UObject* toObject)
{
	AmmoOwner = Cast<IAmmoContainerOwner>(toObject);

	if (AmmoOwner == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Object which weapon was attached to is not an IAmmoContainerOwner"));
}

IWeapon* UBaseWeaponController::GetWeapon()
{
	return Weapon;
}

void UBaseWeaponController::Reload()
{
	if (AmmoOwner == nullptr)
		return;

	Clip->Reload(AmmoOwner->GetAmmoContainer());
}

void UBaseWeaponController::TriggerDown()
{
}

void UBaseWeaponController::TriggerUp()
{
}

void UBaseWeaponController::MakeOneShot()
{
	if (Weapon == nullptr)
		return;

	if (Clip->TrySpend(1))
	{
		Weapon->MakeOneShot();
		
		if (ActivateOnShot.Num() > 0)
		{
			for (const auto comp : ActivateOnShot)
			{
				if (comp != nullptr)
					comp->Activate();
			}
		}
	}

}
