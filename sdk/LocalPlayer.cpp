#include "localPlayer.h"
#include "../memory/memory.h"
#include "../Offsets.h"
#include <optional>

LocalPlayer::LocalPlayer(uintptr_t baseAddr) : Entity(baseAddr) {}


std::optional <uintptr_t> LocalPlayer::getWeaponPtr() const
{
    if(baseAddr == 0) 
        return std::nullopt;

    return mem.readProcess <uintptr_t> (baseAddr + offsets::mPlayer::pCurrentWeapon);
}

std::optional<float>LocalPlayer::getPitch() const
{
    if(baseAddr == 0)
        return std::nullopt;

    return mem.readProcess<float>(baseAddr + offsets::mPlayer::fPitch);
}

bool LocalPlayer::setPitch(float degreesValue)
{
    if(baseAddr == 0 || degreesValue > 89.0f || degreesValue < -89.0f)
        return false;

    return mem.writeProcess<float>(baseAddr + offsets::mPlayer::fPitch, degreesValue);
}

std::optional<float>LocalPlayer::getYaw() const
{
    if(baseAddr == 0)
        return std::nullopt;

    return mem.readProcess<float>(baseAddr + offsets::mPlayer::fYaw);
}

bool LocalPlayer::setYaw(float degreesValue)
{
    if(baseAddr == 0)
        return false;

    return mem.writeProcess<float>(baseAddr + offsets::mPlayer::fYaw, degreesValue);
}