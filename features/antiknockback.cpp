#include "antiknockback.h"

bool AntiKnockBack::enebleAntiKnockBack(Weapon& weapon,bool enable, int16_t knockBackValue)
{
    if(enable)
    {
        weapon.saveStatsWeapon();
        return weapon.setKnockBack(knockBackValue);
    }
    else
    {
        return weapon.restoreWeapon();
    }
    return false;
}
