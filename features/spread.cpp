#include "spread.h"

bool Spread::enableNoSpread(Weapon& weapon,bool enable, int16_t spreadValue)
{
    if(enable)
    {
        weapon.saveStatsWeapon();
        return weapon.setSpreadWeapon(spreadValue);
    }
    else
    {
        return weapon.restoreWeapon();
    }
    return false;
}
