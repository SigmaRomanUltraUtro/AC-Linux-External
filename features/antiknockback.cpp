#include "antiknockback.h"
#include <algorithm>

AntiKnockBack::AntiKnockBack(int16_t valueKnock) : modifiedKnockValue(valueKnock){}

bool AntiKnockBack::update(LocalPlayer& lPlayer, Weapon& weapon)
{
    auto wpPtr = lPlayer.getWeaponPtr();

    if(!wpPtr) return false;

    auto [it, insert] = historyKnock.try_emplace(*wpPtr, 0);

    if(insert)
    {
        auto value = weapon.getKnockBack();

        if(!value)
        {
            historyKnock.erase(*wpPtr);
            return false;
        }

        it->second = *value;
    }

    weapon.setKnockBack(modifiedKnockValue);

    return true;
}

bool AntiKnockBack::disable(LocalPlayer& lPlayer)
{
    for(const auto& [wpPtr, value] : historyKnock)
    {
        Weapon currentWeapon(wpPtr);

        currentWeapon.setKnockBack(value);
    }
    historyKnock.clear();
    return true;
}

void AntiKnockBack::cfgUpdate(const Setting& config)
{
    modifiedKnockValue = config.Knock.Knockvalue;
}

void AntiKnockBack::setKnockValue(int16_t knockValue)
{
    modifiedKnockValue = std::clamp(knockValue, (int16_t)0, (int16_t)500);

    modifiedKnockValue = knockValue;
}
