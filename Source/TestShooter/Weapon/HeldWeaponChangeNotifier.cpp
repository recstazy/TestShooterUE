#include "HeldWeaponChangeNotifier.h"

void UHeldWeaponChangeNotifier::CallWeaponChanged()
{
	OnHeldWeaponChanged.Broadcast();
}
