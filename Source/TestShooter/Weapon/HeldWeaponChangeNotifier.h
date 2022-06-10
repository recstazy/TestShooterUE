#pragma once

#include "CoreMinimal.h"
#include "HeldWeaponChangeNotifier.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHeldWeaponChangedSignature);

UCLASS()
class TESTSHOOTER_API UHeldWeaponChangeNotifier : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CallWeaponChanged();
	
public:
	UPROPERTY(BlueprintAssignable)
	FHeldWeaponChangedSignature OnHeldWeaponChanged;
};
