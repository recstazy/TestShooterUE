#include "PlayerHealthWidget.h"

#include "Kismet/GameplayStatics.h"
#include "TestShooter/Core/TestShooterGameMode.h"
#include "TestShooter/HealthSystem/IHealthOwner.h"

void UPlayerHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	PlayerSpawned(GetWorld()->GetFirstPlayerController()->GetPawn());
	const auto gameMode = Cast<ATestShooterGameMode>(UGameplayStatics::GetGameMode(this));
	gameMode->OnPlayerSpawned.AddDynamic(this, &UPlayerHealthWidget::PlayerSpawned);
}

void UPlayerHealthWidget::UpdateView()
{
	if (HealthSystem == nullptr || HealthBar == nullptr)
		return;

	const float curHealth = HealthSystem->GetCurrentHealth();
	const float maxHealth = HealthSystem->GetMaxHealth();
	HealthBar->SetPercent(curHealth / maxHealth);
}

void UPlayerHealthWidget::HealthSystemChanged(UHealthSystem* healthSystem)
{
	UpdateView();
}

void UPlayerHealthWidget::PlayerSpawned(AActor* playerActor)
{
	// Unsubscribe from old player pawn
	if (HealthSystem != nullptr)
		HealthSystem->OnHealthChanged.RemoveDynamic(this, &UPlayerHealthWidget::HealthSystemChanged);

	// Subscribe to new player pawn
	const auto healthOwner = Cast<IHealthOwner>(playerActor);
	if (healthOwner == nullptr)
		return;
	
	HealthSystem = healthOwner->GetHealthSystem();
	HealthSystem->OnHealthChanged.AddDynamic(this, &UPlayerHealthWidget::HealthSystemChanged);
	UpdateView();
}
