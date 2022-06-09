#include "CollectableHealth.h"

#include "HealthOwner.h"

ACollectableHealth::ACollectableHealth()
{
	PrimaryActorTick.bCanEverTick = true;
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	RootComponent = Sphere;
	Sphere->InitSphereRadius(50.0f);
}

void ACollectableHealth::OnCollected(UObject* collectedObject)
{
	const auto healthOwner = Cast<IHealthOwner>(collectedObject);

	if (healthOwner == nullptr)
		return;

	healthOwner->GetHealthSystem()->Heal(HealthAmount);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Health Collected"));
	Destroy();
}

