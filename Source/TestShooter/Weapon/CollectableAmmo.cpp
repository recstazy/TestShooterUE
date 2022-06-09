#include "CollectableAmmo.h"

#include "AmmoContainerOwner.h"

ACollectableAmmo::ACollectableAmmo()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->InitSphereRadius(50.0f);
}

void ACollectableAmmo::OnCollected(AActor* collectedActor)
{
	const auto ammoContainerOwner = Cast<IAmmoContainerOwner>(collectedActor);
	if (ammoContainerOwner == nullptr)
		return;

	const bool wasCollected = ammoContainerOwner->GetAmmoContainer()->TryAddAmmo(AmmoAmount);
	if (!wasCollected)
		return;;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I'm collected"));
	Destroy();
}
