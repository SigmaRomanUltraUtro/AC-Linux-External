#ifndef RAPIDFIRE_H
#define RAPIDFIRE_H
#include "../features/modifier.h"

class RapidFire : public Modifier
{
private:
    int modifiedDelayValue = 0;
    std::map<uintptr_t ,int> historyDelayWeapon;
public:
    RapidFire(int delayValue);

    bool update(LocalPlayer& lPlayer, Weapon& weapon) override;
    bool disable(LocalPlayer& lPlayer) override;
    void cfgUpdate(const Setting& config) override;
    void setDelay(int delayValue);
};

#endif // RAPIDFIRE_H
