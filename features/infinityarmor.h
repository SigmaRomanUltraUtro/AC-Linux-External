#ifndef INFINITYARMOR_H
#define INFINITYARMOR_H
#include "../features/modifier.h"

class InfinityArmor : public Modifier
{
private:
    int modifiedArmorValue = 0;
    int originalArmorValue = 0;
    bool isActive = false;
public:
    InfinityArmor(int armorValue);

    bool update(LocalPlayer& lPlayer, Weapon& weapon) override;
    bool disable(LocalPlayer& lPlayer) override;
    void cfgUpdate(const Setting& config) override {}
    void SetArmor(int arrmorValue);
};

#endif // INFINITYARMOR_H
