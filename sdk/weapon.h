#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>
#include <optional>
#include "../memory/memory.h"

struct RecoilInfo
{
    int16_t base;
    int16_t increment;
    int16_t max;
};

class Weapon
{
private:

    Memory& mem;
    uintptr_t weaponPtr;

private:
    std::optional <uintptr_t> readDataAmmoSetting() const;

    std::optional <uintptr_t> readDataFireSetting() const;

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

    bool setRecoil(const int16_t base, const int16_t increment, const int16_t max);
};

#endif // WEAPON_H
