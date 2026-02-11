#include "infinityammo.h"
#include <algorithm>

InfinityAmmo::InfinityAmmo(int ammoValue) : modifiedAmmoValue(ammoValue){}

bool InfinityAmmo::update(LocalPlayer& lPlayer, Weapon& weapon)
{
    auto wpPtr = lPlayer.getWeaponPtr();

    if(!wpPtr) return false;

    auto [it, insert] = historyAmmoWeapon.try_emplace(*wpPtr, 0);

    if(insert)
    {
        auto value = weapon.getAmmoWeapon();

        if(!value)
        {
            historyAmmoWeapon.erase(*wpPtr);
            return false;
        }

        it->second = *value;
    }

    weapon.setAmmoWeapon(modifiedAmmoValue);

    return true;
}

bool InfinityAmmo::disable(LocalPlayer& lPlayer)
{
    for(const auto& [wpPtr, value] : historyAmmoWeapon)
    {
        Weapon currentWeapon(wpPtr);

        currentWeapon.setAmmoWeapon(value);
    }
    historyAmmoWeapon.clear();
    return true;
}

void InfinityAmmo::setAmmo(int ammoValue)
{
    modifiedAmmoValue = std::clamp(ammoValue, (int)0, (int)10000);
}
