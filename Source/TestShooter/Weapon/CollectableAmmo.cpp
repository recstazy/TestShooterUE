#include "CollectableAmmo.h"

ACollectableAmmo::ACollectableAmmo()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->InitSphereRadius(50.0f);
}

void ACollectableAmmo::OnCollected(AActor* collectedActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I'm collected"));
	Destroy();
}
