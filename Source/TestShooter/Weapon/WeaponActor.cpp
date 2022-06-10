#include "WeaponActor.h"
#include "IWeaponHolder.h"
#include "WeaponClip.h"

AWeaponActor::AWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	RootComponent = Mesh;
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	CollectableTrigger = CreateDefaultSubobject<USphereComponent>("CollectableTrigger");
	CollectableTrigger->SetCollisionProfileName("Trigger");
	CollectableTrigger->SetGenerateOverlapEvents(true);
	
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

void AWeaponActor::OverrideShootOrigin(USceneComponent* inOrigin)
{
	IWeapon* iWeapon = WeaponController->GetWeapon();

	if (iWeapon != nullptr)
		iWeapon->OverrideShootOrigin(inOrigin);
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
