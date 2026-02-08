#include "weapon.h"
#include "../memory/memory.h"
#include <cstdint>
#include "../Offsets.h"

Weapon::Weapon(const uintptr_t weaponPtr) : weaponPtr(weaponPtr), mem(Memory::get()) {}

std::optional <uintptr_t> Weapon::readPtrFireSetting() const
{
    if(weaponPtr == 0) return std::nullopt;

    return mem.readProcess<uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);
}

std::optional <uintptr_t> Weapon::readPtrAmmoSetting() const
{
    if(weaponPtr == 0) return std::nullopt;

    return mem.readProcess<uintptr_t> (weaponPtr + offsets::Weapon::pAmmoData);
}

std::optional <uintptr_t> Weapon::readPtrGunStats() const
{
    if(weaponPtr == 0) return std::nullopt;

    return mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pGunStats);
}

std::optional <int> Weapon::getWeaponId() const
{
    if(weaponPtr == 0) return std::nullopt;

    return mem.readProcess <int> (weaponPtr + offsets::Weapon::iWeaponID);
}

bool Weapon::setWeaponId(const int& weaponId)
{
    if(weaponId < 0 || weaponPtr == 0) return false;

    return mem.writeProcess <int> (weaponPtr + offsets::Weapon::iWeaponID, weaponId);
}

std::optional <int> Weapon::getAmmoWeapon() const
{
    if(auto ammoSetting = readPtrAmmoSetting())
    {
        return mem.readProcess <int> (*ammoSetting + offsets::AmmoData::iAmmo);
    }

    return std::nullopt;
}

bool Weapon::setAmmoWeapon(const int& ammoWeapon)
{
    if(ammoWeapon <= 0) return false;

    if(auto ammoSetting = readPtrAmmoSetting())
    {
        return mem.writeProcess <int> (*ammoSetting + offsets::AmmoData::iAmmo, ammoWeapon);
    }

    return false;
}


std::optional <int16_t> Weapon::getKnockBack() const
{
    if(auto fireSetting = readPtrFireSetting())
    {
        return mem.readProcess <int16_t> (*fireSetting + offsets::FireSettings::sKnockBack);
    }

    return std::nullopt;
}

bool Weapon::setKnockBack(const int16_t& value)
{
    if(value < 0 || value > 100) return false;

    if(auto fireSetting = readPtrFireSetting())
    {
        return mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sKnockBack, value);
    }

    return false;
}

std::optional <int16_t> Weapon::getSpreadWeapon() const
{
    if(auto fireSetting = readPtrFireSetting())
    {
        return mem.readProcess <uint16_t> (*fireSetting + offsets::FireSettings::sSpread);
    }

    return std::nullopt;
}

bool Weapon::setSpreadWeapon(const int16_t& value)
{
    if(value < 0 || value > 100) return false;

    if(auto fireSetting = readPtrFireSetting())
    {
        return mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sSpread, value);
    }

    return false;
}


std::optional <RecoilInfo> Weapon::getRecoil() const
{

    if(auto fireSetting = readPtrFireSetting())
    {
        auto recBase = mem.readProcess <int16_t> (*fireSetting + offsets::FireSettings::sRecoilBase);
        auto recInc = mem.readProcess <int16_t> (*fireSetting + offsets::FireSettings::sRecoilIncrement);
        auto recMax = mem.readProcess <int16_t> (*fireSetting + offsets::FireSettings::sMaxRecoil);

        if(recBase && recInc && recMax) return RecoilInfo { *recBase,*recInc,*recMax };
    }

    return std::nullopt;
}

bool Weapon::setRecoil(const int16_t base, const int16_t increment, const int16_t max)
{
    if (base < 0 || increment < 0 || max < 0) return false;
    if (base > 1000 || increment > 1000 || max > 1000) return false;

    if(auto fireSetting = readPtrFireSetting())
    {

    bool baseRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sRecoilBase, base);

    bool incrementRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sRecoilIncrement, increment);

    bool maxRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sMaxRecoil, max);

    return baseRecoil && incrementRecoil && maxRecoil;

    }

    return false;
}


bool Weapon::saveStatsWeapon()
{
    if(weaponPtr == 0) return false;

    if(historyStatsWeapon.find(weaponPtr) != historyStatsWeapon.end()) return false;

    auto ammo = getAmmoWeapon();

    auto spread = getSpreadWeapon();

    auto knockback = getKnockBack();

    auto sRecoil = getRecoil();

    if(ammo && spread && knockback && sRecoil)
    {
        WeaponState state;
        state.ammo = *ammo;
        state.recoil = *sRecoil;
        state.knockback = *knockback;
        state.spread = *spread;

        historyStatsWeapon[weaponPtr] = state;
        return true;
    }
    return false;
}

bool Weapon::restoreWeapon()
{
    if(auto it = historyStatsWeapon.find(weaponPtr); it != historyStatsWeapon.end())
    {
        WeaponState& state = it->second;

        setAmmoWeapon(state.ammo);
        setSpreadWeapon(state.spread);
        setKnockBack(state.knockback);
        setRecoil(state.recoil.base,state.recoil.increment,state.recoil.max);

        historyStatsWeapon.erase(it);
        return true;
    }
    return false;
}


std::optional <int> Weapon::getAttackDelay() const
{
    if(auto gunStats = readPtrGunStats())
    {
        return mem.readProcess <int> (*gunStats + offsets::GunStats::iAttackDelay);
    }

    return false;
}

bool Weapon::setAttackDelay(int attackDelay)
{
    if(attackDelay < 0 || attackDelay > 500) return false;

    if(auto gunStats = readPtrGunStats())
    {
        return mem.writeProcess <int> (*gunStats + offsets::GunStats::iAttackDelay, attackDelay);
    }

    return false;
}
