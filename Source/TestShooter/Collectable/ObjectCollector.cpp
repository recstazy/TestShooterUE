#include "ObjectCollector.h"
#include "Collectable.h"

UObjectCollector::UObjectCollector()
{
	SetGenerateOverlapEvents(true);
	SetCollisionProfileName("OverlapAllDynamic");
	OnComponentBeginOverlap.AddDynamic(this, &UObjectCollector::OnOverlapBegin);
}

void UObjectCollector::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto collectable = Cast<ICollectable>(OtherActor);

	if (collectable == nullptr)
		return;

	collectable->OnCollected(GetOwner());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Collectable collected"));
}
