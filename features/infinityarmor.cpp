#include "infinityarmor.h"
#include <algorithm>

InfinityArmor::InfinityArmor(int armorValue) : modifiedArmorValue(armorValue) {}

bool InfinityArmor::update(LocalPlayer& lPlayer, Weapon& weapon)
{
    if(!isActive)
    {
        auto value = lPlayer.getArmor();

        if(!value) return false;

        originalArmorValue = *value;
        isActive = true;
    }
    return lPlayer.setHealth(modifiedArmorValue);
}

bool InfinityArmor:: disable(LocalPlayer& lPlayer)
{
    if(isActive)
    {
        return lPlayer.setArmor(originalArmorValue);
        isActive = false;
    }
    return false;
}

void InfinityArmor::SetArmor(int armorValue)
{
    modifiedArmorValue = std::clamp(armorValue, (int)0, (int)10000);
}
