#ifndef INFINITYAMMO_H
#define INFINITYAMMO_H
#include <map>
#include "../features/modifier.h"

class InfinityAmmo : public Modifier
{
private:
    int modifiedAmmoValue = 0;
    std::map<uintptr_t ,int> historyAmmoWeapon;
public:
    InfinityAmmo(int ammoValue);

    bool update(LocalPlayer& lPlayer, Weapon& weapon) override;
    bool disable(LocalPlayer& lPlayer) override;
    void cfgUpdate(const Setting& config) override {}
    void setAmmo(int ammoValue);
};

#endif // INFINITYAMMO_H
