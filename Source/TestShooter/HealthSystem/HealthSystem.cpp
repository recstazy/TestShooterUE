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
	OnDamage.Broadcast();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HS Damaged: %f"), damage));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Health %f"), CurrentHealth));
	
	const bool isStillAlive = resultHealth > 0.0f;
	
	if (!isStillAlive)
		HandleDeath();

	return initialHealth - CurrentHealth;
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
	CurrentHealth = MaxHealth;
	bIsAlive = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Health %f"), CurrentHealth));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Max Health %f"), MaxHealth));
	Super::BeginPlay();
}

void UHealthSystem::HandleDeath()
{
	bIsAlive = false;
	OnDeath.Broadcast();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HS Dead"));
}

