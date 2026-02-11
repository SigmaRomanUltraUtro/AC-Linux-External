#ifndef MODIFIER_H
#define MODIFIER_H
#include "../sdk/localPlayer.h"
#include "../sdk/weapon.h"
#include "../SettingFunction.h"

class Modifier
{
public:
    virtual bool update(LocalPlayer& lPlayer, Weapon& weapon) = 0;
    virtual bool disable(LocalPlayer& lPlayer) = 0;
    virtual void cfgUpdate(const Setting& config) = 0;
    virtual ~Modifier() = default;
};

#endif // MODIFIER_H
