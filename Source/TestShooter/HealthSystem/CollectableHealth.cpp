#include "CollectableHealth.h"

#include "IHealthOwner.h"

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
	Destroy();
}

