#include "PlayerHealthWidget.h"
#include "TestShooter/HealthSystem/IHealthOwner.h"

void UPlayerHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const auto healthOwner = Cast<IHealthOwner>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (healthOwner == nullptr)
		return;
	
	HealthSystem = healthOwner->GetHealthSystem();
	HealthSystem->OnHealthChanged.AddDynamic(this, &UPlayerHealthWidget::HealthSystemChanged);
	UpdateView();
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
