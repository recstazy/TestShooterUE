#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HeldWeaponChangeNotifier.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHeldWeaponChangedSignature);

UCLASS()
class TESTSHOOTER_API UHeldWeaponChangeNotifier : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FHeldWeaponChangedSignature OnHeldWeaponChanged;

public:
	UFUNCTION(BlueprintCallable)
	static UHeldWeaponChangeNotifier* Construct();
};
