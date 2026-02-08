#include "norecoil.h"

bool NoRecoil::enableNoRecoil(Weapon& weapon, bool enable, int16_t base, const int16_t increment, const int16_t max)
{
    if(enable)
    {
        weapon.saveStatsWeapon();
        return weapon.setRecoil(base,increment,max);
    }
    else
    {
        return weapon.restoreWeapon();
    }
    return false;
}
