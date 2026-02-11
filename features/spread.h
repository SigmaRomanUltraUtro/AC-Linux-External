#ifndef SPREAD_H
#define SPREAD_H
#include "../features/modifier.h"

class Spread : public Modifier
{
private:
    int16_t modifiedSpreadValue = 0;
    std::map<uintptr_t ,int16_t> historySpreadWeapon;
public:
    Spread(int16_t spreadValue);

    bool update(LocalPlayer& lPlayer, Weapon& weapon) override;
    bool disable(LocalPlayer& lPlayer) override;
    void cfgUpdate(const Setting& config) override;
    void setSpread(int16_t spreadValue);
};

#endif // SPREAD_H
