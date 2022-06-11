#include "CollectableAmmo.h"

#include "IAmmoContainerOwner.h"

ACollectableAmmo::ACollectableAmmo()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->InitSphereRadius(50.0f);
}

void ACollectableAmmo::OnCollected(UObject* collectedObject)
{
	const auto ammoContainerOwner = Cast<IAmmoContainerOwner>(collectedObject);
	if (ammoContainerOwner == nullptr)
		return;

	const bool wasCollected = ammoContainerOwner->GetAmmoContainer()->TryAddAmmo(AmmoAmount);
	if (!wasCollected)
		return;;
	
	Destroy();
}
