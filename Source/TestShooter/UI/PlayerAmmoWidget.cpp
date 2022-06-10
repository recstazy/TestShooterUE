#include "PlayerAmmoWidget.h"

#include "TestShooter/Weapon/BaseWeaponController.h"

void UPlayerAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WeaponHolder = Cast<IWeaponHolder>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (WeaponHolder == nullptr)
		return;

	WeaponHolder->GetHeldWeaponChangedNotifier()->OnHeldWeaponChanged.AddDynamic(this, &UPlayerAmmoWidget::HeldWeaponChanged);
	HeldWeaponChanged();
	UpdateView();
}

void UPlayerAmmoWidget::UpdateView()
{
	if (AmmoText == nullptr)
		return;

	const auto weaponController = CurrentWeaponController;
	const bool isWeaponValid = weaponController != nullptr;
	AmmoText->SetVisibility(isWeaponValid ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if (!isWeaponValid)
		return;
	
	const int clipAmmo = weaponController->GetClip()->GetCurrentAmmo();
	const int containerAmmo = weaponController->GetAmmoOwner()->GetAmmoContainer()->GetCurrentAmmo();
	const auto text = FText::Format(FTextFormat::FromString("%d/%d"), clipAmmo, containerAmmo);
	AmmoText->SetText(text);
}

UBaseWeaponController* UPlayerAmmoWidget::GetWeaponController() const
{
	UBaseWeaponController* weaponController = nullptr;

	if (WeaponHolder != nullptr)
	{
		const auto weapon = WeaponHolder->GetWeapon();
		if (weapon != nullptr)
			weaponController = Cast<UBaseWeaponController>(weapon->GetWeaponController());
	}

	return weaponController;
}

void UPlayerAmmoWidget::HeldWeaponChanged()
{
	if (CurrentWeaponController != nullptr)
	{
		CurrentWeaponController->GetClip()->OnCurrentAmmoChanged.RemoveDynamic(this, &UPlayerAmmoWidget::ClipAmmoChanged);
		CurrentWeaponController->GetAmmoOwner()->GetAmmoContainer()->OnAmmoChanged.RemoveDynamic(this, &UPlayerAmmoWidget::ContainerAmmoChanged);
	}

	CurrentWeaponController = GetWeaponController();

	if (CurrentWeaponController != nullptr)
	{
		CurrentWeaponController->GetClip()->OnCurrentAmmoChanged.AddDynamic(this, &UPlayerAmmoWidget::ClipAmmoChanged);
		CurrentWeaponController->GetAmmoOwner()->GetAmmoContainer()->OnAmmoChanged.AddDynamic(this, &UPlayerAmmoWidget::ContainerAmmoChanged);
	}
}

void UPlayerAmmoWidget::ClipAmmoChanged(int currentAmmo)
{
	UpdateView();
}

void UPlayerAmmoWidget::ContainerAmmoChanged(int currentAmmo)
{
	UpdateView();
}
