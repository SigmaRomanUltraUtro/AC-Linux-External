#include "rapidfire.h"

bool RapidFire::enableRapidFire(Weapon& weapon, bool enable)
{
    if(enable)
    {
        weapon.saveStatsWeapon();
        return weapon.setAttackDelay(0);
    }
    else
    {
        return weapon.restoreWeapon();
    }
}
