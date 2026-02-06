#include "weapon.h"
#include "../memory/memory.h"
#include <cstdint>
#include "../Offsets.h"

Weapon::Weapon(const uintptr_t weaponPtr) : weaponPtr(weaponPtr) {}

std::optional <int> Weapon::getWeaponId() const
{
    auto& mem = Memory::get();

    return mem.readProcess <int> (weaponPtr + offsets::Weapon::iWeaponID);
}

bool Weapon::setWeaponId(const int& weaponId)
{
    auto& mem = Memory::get();

    return mem.writeProcess <int> (weaponPtr + offsets::Weapon::iWeaponID, weaponId);
}

std::optional <int> Weapon::getAmmoWeapon() const
{
    auto& mem = Memory::get();

    auto dataAmmo = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pAmmoData);

    if(!dataAmmo) return std::nullopt;

    return mem.readProcess <int> (*dataAmmo + offsets::AmmoData::iAmmo);
}

bool Weapon::setAmmoWeapon(const int& ammoWeapon)
{
    auto& mem = Memory::get();

    auto dataAmmo = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pAmmoData);

    if(!dataAmmo) return false;

    return mem.writeProcess <int> (*dataAmmo + offsets::AmmoData::iAmmo, ammoWeapon);
}


std::optional <int16_t> Weapon::getKnockBack() const
{
    auto& mem = Memory::get();

    auto fireSetting = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);

    if(!fireSetting) return std::nullopt;

    return mem.readProcess <uint16_t> (*fireSetting + offsets::FireSettings::sKnockBack);
}

bool Weapon::setKnockBack(const int16_t& value)
{
    auto& mem = Memory::get();

    auto fireSetting = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);

    if(!fireSetting) return false;

    return mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sKnockBack, value);
}

std::optional <int16_t> Weapon::getSpreadWeapon() const
{
    auto& mem = Memory::get();

    auto fireSetting = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);

    if(!fireSetting) return std::nullopt;

    return mem.readProcess <uint16_t> (*fireSetting + offsets::FireSettings::sSpread);
}

bool Weapon::setSpreadWeapon(const int16_t& value)
{
    auto& mem = Memory::get();

    auto fireSetting = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);

    if(!fireSetting) return false;

    return mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sSpread, value);
}


std::optional <RecoilInfo> Weapon::getRecoil() const
{
    auto& mem = Memory::get();

    auto fireSetting = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);

    if(!fireSetting) return std::nullopt;

    return RecoilInfo
    {
    *mem.readProcess <int16_t> (*fireSetting + offsets::FireSettings::sRecoilBase),
    *mem.readProcess <int16_t> (*fireSetting + offsets::FireSettings::sRecoilIncrement),
    *mem.readProcess <int16_t> (*fireSetting + offsets::FireSettings::sMaxRecoil)
    };
}

bool Weapon::setRecoil(const int16_t base, const int16_t increment, const int16_t max)
{
    auto& mem = Memory::get();

    auto fireSetting = mem.readProcess <uintptr_t> (weaponPtr + offsets::Weapon::pFireSettings);

    if(!fireSetting) return false;

    bool baseRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sRecoilBase, base);

    bool incrementRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sRecoilIncrement, increment);

    bool maxRecoil = mem.writeProcess <uint16_t> (*fireSetting + offsets::FireSettings::sMaxRecoil, max);

    return baseRecoil && incrementRecoil && maxRecoil;
}
