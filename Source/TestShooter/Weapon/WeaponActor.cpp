#include "WeaponActor.h"
#include "IWeaponHolder.h"
#include "WeaponClip.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Clip = CreateDefaultSubobject<UWeaponClip>("WeaponClip");
}

void AWeaponActor::OnCollected(UObject* collectedObject)
{
	const auto holder = Cast<IWeaponHolder>(collectedObject);
	if (holder == nullptr)
		return;

	holder->PickUpWeapon(this);
}

IWeaponController* AWeaponActor::GetWeaponController() const
{
	return WeaponController;
}

void AWeaponActor::GetWeaponControllerBP(TScriptInterface<IWeaponController>& outController) const
{
	outController = Cast<UObject>(GetWeaponController());
}

void AWeaponActor::BeginPlay()
{
	auto controllers = GetComponentsByInterface(UWeaponController::StaticClass());
	
	if (controllers.Num() > 0)
		WeaponController = Cast<IWeaponController>(controllers[0]);
	else
		UE_LOG(LogTemp, Error, TEXT("Weapon Controller not found on Weapon Actor"));
	
	Super::BeginPlay();
}
