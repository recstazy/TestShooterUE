// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestShooterCharacter.h"
#include "TestShooterProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ATestShooterCharacter

ATestShooterCharacter::ATestShooterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(GetFirstPersonCameraComponent());
	FP_MuzzleLocation->ResetRelativeTransform();

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;

	ObjectCollectorComp = CreateDefaultSubobject<UObjectCollector>(TEXT("ObjectCollectorComponent"));
	ObjectCollectorComp->SetupAttachment(RootComponent);
	ObjectCollectorComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ObjectCollectorComp->InitSphereRadius(100.0f);

	Health = CreateDefaultSubobject<UHealthSystem>(TEXT("HealthSystem"));
	AmmoContainer = CreateDefaultSubobject<UAmmoContainer>(TEXT("AmmoContainer"));
	// HeldWeaponChangeNotifier = CreateDefaultSubobject<UHeldWeaponChangeNotifier>("WeaponChangeNotifier");
}

UHealthSystem* ATestShooterCharacter::GetHealthSystem()
{
	return Health;
}

UAmmoContainer* ATestShooterCharacter::GetAmmoContainer()
{
	return AmmoContainer;
}

void ATestShooterCharacter::PickUpWeapon(AWeaponActor* weaponActor)
{
	if (Weapon == weaponActor)
		return;
	
	if (Weapon != nullptr)
	{
		if (!bUsingMotionControllers)
			Weapon->OverrideShootOrigin(nullptr);

		Weapon->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	}
	
	Weapon = weaponActor;
	weaponActor->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	weaponActor->GetWeaponController()->Attached(this);

	if (!bUsingMotionControllers)
		Weapon->OverrideShootOrigin(FP_MuzzleLocation);
	
	HeldWeaponChangeNotifier->CallWeaponChanged();
}

AWeaponActor* ATestShooterCharacter::GetWeapon() const
{
	return Weapon;
}

UHeldWeaponChangeNotifier* ATestShooterCharacter::GetHeldWeaponChangedNotifier() const
{
	return HeldWeaponChangeNotifier;
}

void ATestShooterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	
	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		Mesh1P->SetHiddenInGame(false, true);
	}
}

void ATestShooterCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	const auto notifier = AddComponentByClass(UHeldWeaponChangeNotifier::StaticClass(), false, FTransform::Identity, false);
	HeldWeaponChangeNotifier = Cast<UHeldWeaponChangeNotifier>(notifier);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATestShooterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATestShooterCharacter::OnTriggerDown);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATestShooterCharacter::OnTriggerUp);

	// Bind reload event
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATestShooterCharacter::OnReload);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATestShooterCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ATestShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATestShooterCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATestShooterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATestShooterCharacter::LookUpAtRate);
}

void ATestShooterCharacter::OnTriggerDown()
{
	if (Weapon == nullptr)
		return;

	Weapon->GetWeaponController()->TriggerDown();
}

void ATestShooterCharacter::OnTriggerUp()
{
	if (Weapon == nullptr)
		return;

	Weapon->GetWeaponController()->TriggerUp();
}

void ATestShooterCharacter::OnReload()
{
	if (Weapon == nullptr)
		return;

	Weapon->GetWeaponController()->Reload();
}

void ATestShooterCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATestShooterCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnTriggerDown();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ATestShooterCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

void ATestShooterCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ATestShooterCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ATestShooterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATestShooterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

bool ATestShooterCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATestShooterCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ATestShooterCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATestShooterCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}