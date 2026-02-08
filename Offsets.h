#ifndef OFFSETS_H
#define OFFSETS_H
#include <cstdint>
namespace offsets
{

constexpr uintptr_t dLocalPlayer = 0x1a3518;

namespace mPlayer
{

constexpr uintptr_t iHealth = 0x100;
constexpr uintptr_t iArmor = 0x104;
constexpr uintptr_t pCurrentWeapon = 0x3a0;
constexpr uintptr_t pStatsArray = 0x184;

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
constexpr uintptr_t sSpread = 0x52;
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
