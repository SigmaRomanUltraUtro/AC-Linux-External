#pragma once
#include "localPlayer.h"
#include "../memory/memory.h"
#include "../Offsets.h"

uintptr_t LocalPlayer::getPlayerAddr() const  { return localPlayerAddr; }

bool LocalPlayer::update()
{
    auto& mem = Memory::get();

    auto base = mem.getBaseAddr("linux_64_client");

    if(base)
    {
        auto pPlayer = mem.readProcess <uintptr_t> (*base + offsets::dLocalPlayer);

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

    auto& mem = Memory::get();

    return mem.readProcess <uintptr_t> (localPlayerAddr + offsets::mPlayer::pCurrentWeapon);
}

std::optional <int> LocalPlayer::getHealth() const
{
    if(localPlayerAddr == 0) return std::nullopt;

    auto& mem = Memory::get();

    return mem.readProcess <int> (localPlayerAddr + offsets::mPlayer::iHealth);
}

bool LocalPlayer::setHealth(const int& value) const
{
    if(localPlayerAddr == 0) return false;

    auto& mem = Memory::get();

    return mem.writeProcess <int> (localPlayerAddr + offsets::mPlayer::iHealth, value);
}


bool LocalPlayer::setArrmor(const int& value) const
{
    if(localPlayerAddr == 0) return false;

    auto& mem = Memory::get();

    return mem.writeProcess <int> (localPlayerAddr + offsets::mPlayer::iArmor, value);
}

std::optional <int> LocalPlayer::getArrmor() const
{
    if(localPlayerAddr == 0) return std::nullopt;

    auto& mem = Memory::get();

    return mem.readProcess <int> (localPlayerAddr + offsets::mPlayer::iArmor);
}





