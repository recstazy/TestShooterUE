#include "CollectableAmmo.h"

ACollectableAmmo::ACollectableAmmo()
{
	
}

void ACollectableAmmo::OnCollected()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("I'm collected"));
	Destroy();
}
