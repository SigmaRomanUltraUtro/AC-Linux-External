#include "norecoil.h"
#include "../kernel.h"

NoRecoil::NoRecoil() : modifiedRecoil{0,0,0} {}

bool NoRecoil::update(LocalPlayer& lPlayer, Weapon& weapon)
{
    auto wpPtr = lPlayer.getWeaponPtr();

    if(!wpPtr) return false;

    auto [it, insert] = historyRecoilWeapon.try_emplace(*wpPtr, RecoilInfo {});

    if(insert)
    {
        auto value = weapon.getRecoil();

        if(!value)
        {
            historyRecoilWeapon.erase(*wpPtr);
            return false;
        }

        it->second = *value;
    }

    weapon.setRecoil(modifiedRecoil);

    return true;
}

bool NoRecoil::disable(LocalPlayer& lPlayer)
{
    for(const auto& [wpPtr, value] : historyRecoilWeapon)
    {
        Weapon currentWeapon(wpPtr);

        currentWeapon.setRecoil(value);
    }
    historyRecoilWeapon.clear();
    return true;
}

void NoRecoil::cfgUpdate(const Setting& config)
{
    modifiedRecoil.base = config.Recoil.recoilBase;
    modifiedRecoil.inc = config.Recoil.recoilInc;
    modifiedRecoil.max = config.Recoil.recoilMax;
}

bool NoRecoil::setRecoil(const RecoilInfo& recoil)
{
    if(!recoil.isValid()) return false;

    modifiedRecoil = recoil;

    return true;
}
