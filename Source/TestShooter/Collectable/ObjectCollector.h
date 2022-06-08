#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "ObjectCollector.generated.h"

UCLASS()
class TESTSHOOTER_API UObjectCollector : public USphereComponent
{
	GENERATED_BODY()

public:
	UObjectCollector();
		
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
