#include "PlayerAmmoWidget.h"

#include "TestShooter/Weapon/BaseWeaponController.h"

void UPlayerAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	AmmoOwner = Cast<IAmmoContainerOwner>(playerPawn);

	if (AmmoOwner != nullptr)
		AmmoOwner->GetAmmoContainer()->OnAmmoChanged.AddDynamic(this, &UPlayerAmmoWidget::ContainerAmmoChanged);
	
	WeaponHolder = Cast<IWeaponHolder>(playerPawn);
	if (WeaponHolder == nullptr)
		return;

	const auto weaponChangeNotifier = WeaponHolder->GetHeldWeaponChangedNotifier();
	auto message = weaponChangeNotifier == nullptr ? "Notifier is NULL" : "Notifier is NOT null";
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);

	if (weaponChangeNotifier == nullptr)
		return;
	
	weaponChangeNotifier->OnHeldWeaponChanged.AddDynamic(this, &UPlayerAmmoWidget::HeldWeaponChanged);
	HeldWeaponChanged();
}

void UPlayerAmmoWidget::UpdateView()
{
	if (AmmoText == nullptr)
		return;

	int containerAmmo = -1;
	int clipAmmo = -1;
	
	if (AmmoOwner != nullptr)
		containerAmmo = AmmoOwner->GetAmmoContainer()->GetCurrentAmmo();

	if (CurrentWeaponController != nullptr)
		clipAmmo = CurrentWeaponController->GetClip()->GetCurrentAmmo();
	
	const auto text = FText::FromString(FString::Printf(TEXT("%d/%d"), clipAmmo, containerAmmo));
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
		CurrentWeaponController->GetClip()->OnCurrentAmmoChanged.AddDynamic(this, &UPlayerAmmoWidget::ClipAmmoChanged);

	CurrentWeaponController = GetWeaponController();

	if (CurrentWeaponController != nullptr)
		CurrentWeaponController->GetClip()->OnCurrentAmmoChanged.AddDynamic(this, &UPlayerAmmoWidget::ClipAmmoChanged);

	UpdateView();
}

void UPlayerAmmoWidget::ClipAmmoChanged(int currentAmmo)
{
	UpdateView();
}

void UPlayerAmmoWidget::ContainerAmmoChanged(int currentAmmo)
{
	UpdateView();
}
