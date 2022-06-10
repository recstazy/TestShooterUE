// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVoidSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTSHOOTER_API UHealthSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthSystem();

	UFUNCTION(BlueprintCallable)
	float TakeDamage(float damage);

	UFUNCTION(BlueprintCallable)
	void Heal(float amount);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

public:
	UPROPERTY(BlueprintAssignable)
	FVoidSignature OnDamage;

	UPROPERTY(BlueprintAssignable)
	FVoidSignature OnDeath;

	UPROPERTY(BlueprintAssignable)
	FVoidSignature OnHealthChanged;

protected:
	virtual void BeginPlay() override;

private:
	void HandleDeath();

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere)
	bool bIsAlive;
};
