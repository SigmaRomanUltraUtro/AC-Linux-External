#include "infinityammo.h"

bool InfinityAmmo::enableInfinityAmmo(Weapon& weapon, bool enable)
{
    if(enable)
    {
        weapon.saveStatsWeapon();
        return weapon.setAmmoWeapon(9999);
    }
    else
    {
        return weapon.restoreWeapon();
    }
    return false;
}
