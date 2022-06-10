#include "BaseWeaponController.h"

UBaseWeaponController::UBaseWeaponController()
{
	PrimaryComponentTick.bCanEverTick = true;
	Clip = CreateDefaultSubobject<UWeaponClip>("Clip");
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
	const auto weaponComponents = GetOwner()->GetComponentsByInterface(UWeapon::StaticClass());

	if (weaponComponents.Num() > 0)
		Weapon = Cast<IWeapon>(weaponComponents[0]);
	else
		UE_LOG(LogTemp, Error, TEXT("Weapon component not found in Weapon"));
	
	Attached(GetOwner());
	Super::BeginPlay();
}

void UBaseWeaponController::Attached(UObject* toObject)
{
	AmmoOwner = Cast<IAmmoContainerOwner>(toObject);

	if (AmmoOwner == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Object which weapon was attached to is not an IAmmoContainerOwner"));
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

