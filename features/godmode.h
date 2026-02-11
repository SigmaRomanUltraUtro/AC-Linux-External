#ifndef GODMODE_H
#define GODMODE_H
#include "../sdk/localPlayer.h"
#include "../features/modifier.h"

class GodMode : public Modifier
{
public:
    int modifiedHpValue = 0;
    bool isActive = false;
    int originalHpValue = 0;
public:
    GodMode(int Hp);

    bool update(LocalPlayer& lPlayer,Weapon& weapon) override;
    bool disable(LocalPlayer& lPlayer) override;
    void cfgUpdate(const Setting& config) override {}
    void setHpValue(int valueHp);
};

#endif // GODMODE_H
