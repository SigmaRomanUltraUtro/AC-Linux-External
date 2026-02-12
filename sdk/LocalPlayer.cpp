#include "localPlayer.h"
#include "../memory/memory.h"
#include "../Offsets.h"

LocalPlayer::LocalPlayer() : mem(Memory::get()) {}

bool LocalPlayer::update(uintptr_t baseAddr)
{
    if(baseAddr == 0) return false;

    if(baseAddr)
    {
        auto pPlayer = mem.readProcess <uintptr_t> (baseAddr + offsets::dLocalPlayer);

        if(pPlayer && *pPlayer != 0)
        {
            localPlayerAddr = *pPlayer;
            return true;
        }
    }
    localPlayerAddr = 0;
    return false;
}

std::optional <uintptr_t> LocalPlayer::getWeaponPtr() const
{
    if(localPlayerAddr == 0) return std::nullopt;

    return mem.readProcess <uintptr_t> (localPlayerAddr + offsets::mPlayer::pCurrentWeapon);
}

std::optional <int> LocalPlayer::getHealth() const
{
    if(localPlayerAddr == 0) return std::nullopt;

    return mem.readProcess <int> (localPlayerAddr + offsets::mPlayer::iHealth);
}

bool LocalPlayer::setHealth(int value)
{
    if(localPlayerAddr == 0 || value <= 0) return false;

    return mem.writeProcess <int> (localPlayerAddr + offsets::mPlayer::iHealth, value);
}

bool LocalPlayer::setArmor(int value)
{
    if(localPlayerAddr == 0 || value <= 0) return false;

    return mem.writeProcess <int> (localPlayerAddr + offsets::mPlayer::iArmor, value);
}

std::optional <int> LocalPlayer::getArmor() const
{
    if(localPlayerAddr == 0) return std::nullopt;

    return mem.readProcess <int> (localPlayerAddr + offsets::mPlayer::iArmor);
}

std::optional<float>LocalPlayer::getPitch() const
{
    if(localPlayerAddr == 0)
        return std::nullopt;

    return mem.readProcess<float>(localPlayerAddr + offsets::mPlayer::fPitch);
}

bool LocalPlayer::setPitch(float degreesValue)
{
    if(localPlayerAddr == 0 || degreesValue > 89.0f || degreesValue < -89.0f)
        return false;

    return mem.writeProcess<float>(localPlayerAddr + offsets::mPlayer::fPitch, degreesValue);
}

std::optional<float>LocalPlayer::getYaw() const
{
    if(localPlayerAddr == 0)
        return std::nullopt;

    return mem.readProcess<float>(localPlayerAddr + offsets::mPlayer::fYaw);
}

bool LocalPlayer::setYaw(float degreesValue)
{
    if(localPlayerAddr == 0)
        return false;

    return mem.writeProcess<float>(localPlayerAddr + offsets::mPlayer::fYaw, degreesValue);
}