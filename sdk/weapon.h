#ifndef WEAPON_H
#define WEAPON_H
#include <cstdint>
#include <optional>
#include "../memory/memory.h"
#include <map>

struct RecoilInfo
{
    int16_t base;
    int16_t increment;
    int16_t max;
};

struct WeaponState
{
    int16_t spread;
    int ammo;
    int16_t knockback;
    RecoilInfo recoil;
};

static std::map <uintptr_t, WeaponState> historyStatsWeapon;

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

    bool saveStatsWeapon();

    bool restoreWeapon();

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

    std::optional <int> getAttackDelay() const;

    bool setAttackDelay(int attackDelay);
};

#endif // WEAPON_H
