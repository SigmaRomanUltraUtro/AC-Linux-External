#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>
#include <optional>
#include "../memory/memory.h"

struct RecoilInfo
{
    int16_t base;
    int16_t inc;
    int16_t max;

    bool isValid() const
    {
        return base >= 0 && inc >= 0 && max >= 0 &&base <= 1000 && inc <= 1000 && max <= 1000;
    }
};

class Weapon
{
private:
    Memory& mem;
    uintptr_t weaponPtr;

private:
    std::optional <uintptr_t> readPtrAmmoSetting() const;

    std::optional <uintptr_t> readPtrFireSetting() const;

    std::optional <uintptr_t> readPtrGunStats() const;

public:

    Weapon(const uintptr_t weaponPtr);

    std::optional <int> getWeaponId() const;

    bool setWeaponId(const int& weaponId);

    std::optional <int> getAmmoWeapon() const;

    bool setAmmoWeapon(const int& ammo);

    std::optional <int16_t> getKnockBack() const;

    bool setKnockBack(const int16_t& value);

    std::optional <int16_t> getSpreadWeapon() const;

    bool setSpreadWeapon(const int16_t& value);

    std::optional <RecoilInfo> getRecoil() const;

    bool setRecoil(const RecoilInfo& recoil);

    std::optional <int> getAttackDelay() const;

    bool setAttackDelay(int attackDelay);
};

#endif // WEAPON_H
