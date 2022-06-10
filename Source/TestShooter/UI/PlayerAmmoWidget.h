// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TestShooter/Weapon/BaseWeaponController.h"
#include "TestShooter/Weapon/IWeaponHolder.h"
#include "TestShooter/Weapon/WeaponActor.h"
#include "PlayerAmmoWidget.generated.h"

UCLASS()
class TESTSHOOTER_API UPlayerAmmoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* AmmoText;
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void UpdateView();

	UBaseWeaponController* GetWeaponController() const;
	void HeldWeaponChanged();
	void ClipAmmoChanged(int currentAmmo);
	void ContainerAmmoChanged(int currentAmmo);
	
private:
	IWeaponHolder* WeaponHolder;

	UPROPERTY()
	UBaseWeaponController* CurrentWeaponController;
};
