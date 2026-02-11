#include "spread.h"
#include <algorithm>

Spread::Spread(int16_t spreadValue) : modifiedSpreadValue(spreadValue) {}

bool Spread::update(LocalPlayer& lPlayer, Weapon& weapon)
{
    auto wpPtr = lPlayer.getWeaponPtr();

    if(!wpPtr) return false;

    auto [it, insert] = historySpreadWeapon.try_emplace(*wpPtr, 0);

    if(insert)
    {
        auto value = weapon.getSpreadWeapon();

        if(!value)
        {
            historySpreadWeapon.erase(*wpPtr);
            return false;
        }

        it->second = *value;
    }

    weapon.setSpreadWeapon(modifiedSpreadValue);

    return true;
}

bool Spread::disable(LocalPlayer& lPlayer)
{
    for(const auto& [wpPtr, value] : historySpreadWeapon)
    {
        Weapon currentWeapon(wpPtr);

        currentWeapon.setSpreadWeapon(value);
    }
    historySpreadWeapon.clear();
    return true;
}

void Spread::cfgUpdate(const Setting& config)
{
    modifiedSpreadValue = config.Spread.Spreadvalue;
}

void Spread::setSpread(int16_t spreadValue)
{
    modifiedSpreadValue = std::clamp(spreadValue, (int16_t)0, (int16_t)1000);
}
