#include "rapidfire.h"
#include <algorithm>

RapidFire::RapidFire(int delayValue) : modifiedDelayValue(delayValue) {}

bool RapidFire::update(LocalPlayer& lPlayer, Weapon& weapon)
{
    auto wpPtr = lPlayer.getWeaponPtr();

    if(!wpPtr) return false;

    auto [it, insert] = historyDelayWeapon.try_emplace(*wpPtr, 0);

    if(insert)
    {
        auto value = weapon.getAttackDelay();

        if(!value)
        {
            historyDelayWeapon.erase(*wpPtr);
            return false;
        }

        it->second = *value;
    }

    weapon.setAttackDelay(modifiedDelayValue);

    return true;
}

bool RapidFire::disable(LocalPlayer& lPlayer)
{
    for(const auto& [wpPtr, value] : historyDelayWeapon)
    {
        Weapon currentWeapon(wpPtr);

        currentWeapon.setAttackDelay(value);
    }
    historyDelayWeapon.clear();
    return true;
}

void RapidFire::cfgUpdate(const Setting& config) 
{
    modifiedDelayValue = config.Delay.delayValue;
}

void RapidFire::setDelay(int delayValue)
{
    modifiedDelayValue = std::clamp(delayValue, (int)0, (int)1000);
}
