#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"

class UHealthSystem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthSystemSignature, UHealthSystem*, healthSystem);

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
	FHealthSystemSignature OnDamage;

	UPROPERTY(BlueprintAssignable)
	FHealthSystemSignature OnDeath;

	UPROPERTY(BlueprintAssignable)
	FHealthSystemSignature OnHealthChanged;

protected:
	virtual void BeginPlay() override;

private:
	void HandleDeath();

	UFUNCTION()
	void OwnerDamaged(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser);

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess))
	float MaxHealth;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere)
	bool bIsAlive;
};
