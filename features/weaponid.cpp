#include "weaponid.h"

bool WeaponId::weaponId(Weapon& weapon,bool enable, int weaponId)
{
    if(enable)
    {
        return weapon.setWeaponId(weaponId);
    }
    return false;
}
