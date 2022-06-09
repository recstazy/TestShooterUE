#include "RaycastWeaponComp.h"

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

	FHitResult hit;
	const bool wasHit = GetWorld()->LineTraceSingleByChannel(hit, lineStart, lineEnd, TraceChannel);
	if (!wasHit)
		return;

	auto damageEvent = FPointDamageEvent();
	damageEvent.Damage = Damage;
	damageEvent.HitInfo = hit;
	FVector direction = (lineEnd - lineStart);
	direction.Normalize();
	damageEvent.ShotDirection = direction;
	hit.Actor->TakeDamage(Damage, damageEvent, GetOwner()->GetInstigatorController(),GetOwner());
}

