#include "RaycastWeaponComp.h"

#include "WeaponActor.h"

URaycastWeapon::URaycastWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;
	arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootDirection"));
	arrow->SetupAttachment(this);
	arrow->ResetRelativeTransform();
}

void URaycastWeapon::MakeOneShot()
{
	const FVector lineStart = GetComponentLocation();
	const FRotator rotation = GetComponentRotation();
	const FVector lineEnd = lineStart + rotation.Vector() * MaxDistance;

	TArray<AActor*> parentActors;
	GetAllOwnerActors(parentActors);
	
	FHitResult hit;
	auto queryParams = FCollisionQueryParams();
	queryParams.AddIgnoredActors(parentActors);
	const bool wasHit = GetWorld()->LineTraceSingleByChannel(hit, lineStart, lineEnd, TraceChannel, queryParams);
	if (!wasHit)
		return;

	auto damageEvent = FPointDamageEvent();
	damageEvent.Damage = Damage;
	damageEvent.HitInfo = hit;
	FVector direction = (lineEnd - lineStart);
	direction.Normalize();
	damageEvent.ShotDirection = direction;
	hit.Actor->TakeDamage(Damage, damageEvent, GetOwner()->GetInstigatorController(),GetOwner());

	auto primitive = Cast<UPrimitiveComponent>(hit.Actor->GetComponentByClass(UPrimitiveComponent::StaticClass()));

	if (primitive != nullptr && primitive->GetOwner()->IsRootComponentMovable())
		primitive->AddImpulse(direction * 100000.0f);
}

void URaycastWeapon::GetAllOwnerActors(TArray<AActor*>& actors) const
{
	AActor* parent = GetOwner();

	while(parent != nullptr)
	{
		actors.Add(parent);
		parent = parent->GetAttachParentActor();
	}
}

