#include "HealthSystem.h"

UHealthSystem::UHealthSystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UHealthSystem::TakeDamage(float damage)
{
	if (!bIsAlive)
		return 0.0f;

	const float initialHealth = CurrentHealth;
	const float resultHealth = CurrentHealth - damage;
	CurrentHealth = FMath::Clamp(resultHealth, 0.0f, MaxHealth);
	OnDamage.Broadcast(this);
	OnHealthChanged.Broadcast(this);
	const bool isStillAlive = resultHealth > 0.0f;

	if (!isStillAlive)
		HandleDeath();

	return initialHealth - CurrentHealth;
}

void UHealthSystem::Heal(float amount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + amount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(this);
}

bool UHealthSystem::IsAlive() const
{
	return bIsAlive;
}

float UHealthSystem::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthSystem::GetMaxHealth() const
{
	return MaxHealth;
}

void UHealthSystem::BeginPlay()
{
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthSystem::OwnerDamaged);
	
	CurrentHealth = MaxHealth;
	bIsAlive = true;
	OnHealthChanged.Broadcast(this);
	Super::BeginPlay();
}

void UHealthSystem::HandleDeath()
{
	bIsAlive = false;
	OnDeath.Broadcast(this);
}

void UHealthSystem::OwnerDamaged(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* EventInstigator, AActor* DamageCauser)
{
	TakeDamage(DamageAmount);
}

