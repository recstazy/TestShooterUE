#include "SemiAutomaticWeaponController.h"

USemiAutomaticWeaponController::USemiAutomaticWeaponController()
{
	PrimaryComponentTick.bCanEverTick = true;
	Clip = CreateDefaultSubobject<UWeaponClip>("Clip");
	const auto weaponConponents = GetOwner()->GetComponentsByInterface(UWeapon::StaticClass());

	if (weaponConponents.Num() > 0)
		Weapon = Cast<IWeapon>(weaponConponents[0]);
	else
		UE_LOG(LogTemp, Error, TEXT("Weapon component not found in SemiAutomatic Weapon"));
}

void USemiAutomaticWeaponController::Attached(UObject* toObject)
{
	AmmoOwner = Cast<IAmmoContainerOwner>(toObject);

	if (AmmoOwner == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Object which weapon was attached to is not an IAmmoContainerOwner"));
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

void USemiAutomaticWeaponController::Reload()
{
	if (AmmoOwner == nullptr)
		return;
	
	Clip->Reload(AmmoOwner->GetAmmoContainer());
}

void USemiAutomaticWeaponController::BeginPlay()
{
	Attached(GetOwner());
	Super::BeginPlay();
}

