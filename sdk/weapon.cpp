#include "weapon.h"
#include "../memory/memory.h"
#include <cstdint>
#include "../Offsets.h"

Weapon::Weapon(const uintptr_t weaponPtr) : weaponPtr(weaponPtr), mem(Memory::get()) {}

std::optional <uintptr_t> Weapon::readDataFireSetting() const
{
    if(weaponPtr == 0) return std::nullopt;

    return mem.readProcess<uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);
}

std::optional <uintptr_t> Weapon::readDataAmmoSetting() const
{
    if(weaponPtr == 0) return std::nullopt;

    return mem.readProcess<uintptr_t> (weaponPtr + offsets::Weapon::pAmmoData);
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
    if(auto ammoSetting = readDataAmmoSetting())
    {
        return mem.readProcess <int> (*ammoSetting + offsets::AmmoData::iAmmo);
    }

    return std::nullopt;
}

bool Weapon::setAmmoWeapon(const int& ammoWeapon)
{
    if(ammoWeapon <= 0) return false;

    if(auto ammoSetting = readDataAmmoSetting())
    {
        return mem.writeProcess <int> (*ammoSetting + offsets::AmmoData::iAmmo, ammoWeapon);
    }

    return false;
}


std::optional <int16_t> Weapon::getKnockBack() const
{
    if(auto fireSetting = readDataFireSetting())
    {
        return mem.readProcess <uint16_t> (*fireSetting + offsets::FireSettings::sKnockBack);
    }

    return std::nullopt;
}

bool Weapon::setKnockBack(const int16_t& value)
{
    if(value < 0 || value > 100) return false;

    if(auto fireSetting = readDataFireSetting())
    {
        return mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sKnockBack, value);
    }

    return false;
}

std::optional <int16_t> Weapon::getSpreadWeapon() const
{
    if(auto fireSetting = readDataFireSetting())
    {
        return mem.readProcess <uint16_t> (*fireSetting + offsets::FireSettings::sSpread);
    }

    return false;
}

bool Weapon::setSpreadWeapon(const int16_t& value)
{
    if(value < 0 || value > 100) return false;

    if(auto fireSetting = readDataFireSetting())
    {
        return mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sSpread, value);
    }

    return false;
}


std::optional <RecoilInfo> Weapon::getRecoil() const
{

    if(auto fireSetting = readDataFireSetting())
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

    if(auto fireSetting = readDataFireSetting())
    {

    bool baseRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sRecoilBase, base);

    bool incrementRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sRecoilIncrement, increment);

    bool maxRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sMaxRecoil, max);

    return baseRecoil && incrementRecoil && maxRecoil;

    }

    return false;
}
