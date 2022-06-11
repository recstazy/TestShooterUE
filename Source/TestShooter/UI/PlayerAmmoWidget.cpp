#include "PlayerAmmoWidget.h"

#include "Kismet/GameplayStatics.h"
#include "TestShooter/Core/TestShooterGameMode.h"
#include "TestShooter/Weapon/BaseWeaponController.h"

void UPlayerAmmoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	PlayerSpawned(playerPawn);
	const auto gameMode = Cast<ATestShooterGameMode>(UGameplayStatics::GetGameMode(this));
	gameMode->OnPlayerSpawned.AddDynamic(this, &UPlayerAmmoWidget::PlayerSpawned);
}

void UPlayerAmmoWidget::UpdateView()
{
	if (AmmoText == nullptr)
		return;

	int containerAmmo = 0;
	int clipAmmo = 0;
	
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
		CurrentWeaponController->GetClip()->OnCurrentAmmoChanged.RemoveDynamic(this, &UPlayerAmmoWidget::ClipAmmoChanged);

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

void UPlayerAmmoWidget::PlayerSpawned(AActor* playerActor)
{
	// Unsubscribe from old player pawn
	if (AmmoOwner != nullptr)
		AmmoOwner->GetAmmoContainer()->OnAmmoChanged.RemoveDynamic(this, &UPlayerAmmoWidget::ContainerAmmoChanged);
	
	if (WeaponHolder != nullptr)
	{
		const auto notifier = WeaponHolder->GetHeldWeaponChangedNotifier();
		if (notifier != nullptr)
			notifier->OnHeldWeaponChanged.RemoveDynamic(this, &UPlayerAmmoWidget::HeldWeaponChanged);
	}
	
	// Subscribe to new player pawn
	AmmoOwner = Cast<IAmmoContainerOwner>(playerActor);

	if (AmmoOwner != nullptr)
		AmmoOwner->GetAmmoContainer()->OnAmmoChanged.AddDynamic(this, &UPlayerAmmoWidget::ContainerAmmoChanged);
	
	WeaponHolder = Cast<IWeaponHolder>(playerActor);
	if (WeaponHolder == nullptr)
		return;

	const auto weaponChangeNotifier = WeaponHolder->GetHeldWeaponChangedNotifier();
	const auto message = weaponChangeNotifier == nullptr ? "Notifier is NULL" : "Notifier is NOT null";
	const auto color = weaponChangeNotifier == nullptr ? FColor::Red : FColor::Green;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, color, message);

	if (weaponChangeNotifier == nullptr)
		return;
	
	weaponChangeNotifier->OnHeldWeaponChanged.AddDynamic(this, &UPlayerAmmoWidget::HeldWeaponChanged);
	HeldWeaponChanged();
}
