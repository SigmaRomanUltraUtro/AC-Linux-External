#include "godmode.h"
#include <algorithm>

GodMode::GodMode(int Hp) : modifiedHpValue(Hp) {}

bool GodMode::update(LocalPlayer& lPlayer,Weapon& weapon)
{
    if(!isActive)
    {
        auto value = lPlayer.getHealth();

        if(!value) return false;

        originalHpValue = *value;
        isActive = true;
    }
    return lPlayer.setHealth(modifiedHpValue);
}

bool GodMode::disable(LocalPlayer& lPlayer)
{
    if(isActive)
    {
        isActive = false;
        return lPlayer.setHealth(originalHpValue);
    }
    return false;
}

void GodMode::setHpValue(int valueHp)
{
    modifiedHpValue = std::clamp(valueHp, (int)0, (int)10000);
}
