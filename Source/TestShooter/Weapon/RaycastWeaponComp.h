#pragma once

#include "CoreMinimal.h"
#include "IWeapon.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "RaycastWeaponComp.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API URaycastWeapon : public USceneComponent, public IWeapon
{
	GENERATED_BODY()

public:
	URaycastWeapon();
	virtual void MakeOneShot() override;

private:
	UPROPERTY(VisibleInstanceOnly)
	UArrowComponent* arrow;
	
	UPROPERTY(EditDefaultsOnly)
	float MaxDistance;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

private:
	void GetAllOwnerActors(TArray<AActor*>& actors) const;
};
