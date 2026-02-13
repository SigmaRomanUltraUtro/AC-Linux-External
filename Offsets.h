#ifndef OFFSETS_H
#define OFFSETS_H
#include <cstdint>
namespace offsets
{

constexpr uintptr_t dLocalPlayer = 0x1a3518;
constexpr uintptr_t dPlayerCount = 0x1B6648;

namespace players
{
    constexpr uintptr_t fRdius = 0x50;
    constexpr uintptr_t fHeight = 0x54;
    constexpr uintptr_t fAboveEye = 0x5c;

    constexpr uintptr_t fPosX = 0x08;
    constexpr uintptr_t fPosY = 0xC;
    constexpr uintptr_t fPosZ = 0x10;

    constexpr uintptr_t iDead = 0x1;
}

namespace mPlayer
{

constexpr uintptr_t iHealth = 0x100;
constexpr uintptr_t iArmor = 0x104;
constexpr uintptr_t pCurrentWeapon = 0x3a0;
constexpr uintptr_t pStatsArray = 0x184;
constexpr uintptr_t fPitch = 0x3c;
constexpr uintptr_t fYaw = 0x38;

}

namespace Weapon
{

constexpr uintptr_t pOwner = 0x10;
constexpr uintptr_t pFireSettings = 0x18;
constexpr uintptr_t pAmmoData = 0x28;
constexpr uintptr_t iWeaponID = 0x8;
constexpr uintptr_t pGunStats = 0x30;

}

namespace FireSettings
{
constexpr uintptr_t sKnockBack = 0x54;
constexpr uintptr_t sSpread = 0x38;
constexpr uintptr_t sRecoilBase = 0x5C;
constexpr uintptr_t sRecoilIncrement = 0x5E;
constexpr uintptr_t sMaxRecoil = 0x60;


}

namespace GunStats
{
constexpr uintptr_t iAttackDelay = 0x0;
}

namespace AmmoData
{

constexpr uintptr_t  iAmmo = 0x0;

}

}


#endif // OFFSETS_H
