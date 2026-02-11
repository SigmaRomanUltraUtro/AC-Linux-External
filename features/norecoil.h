#ifndef NORECOIL_H
#define NORECOIL_H
#include "../sdk/weapon.h"
#include "../features/modifier.h"
#include <map>

class NoRecoil : public Modifier
{

private:
    RecoilInfo modifiedRecoil;
    std::map<uintptr_t, RecoilInfo> historyRecoilWeapon;
public:
    NoRecoil();
    bool update(LocalPlayer& lPlayer, Weapon& weapon) override;
    bool disable(LocalPlayer& lPlayer) override;
    void cfgUpdate(const Setting& config) override;
    bool setRecoil(const RecoilInfo& recoil);
};

#endif // NORECOIL_H
