#pragma once
#include "localPlayer.h"
#include "../memory/memory.h"
#include "../Offsets.h"

std::optional <uintptr_t> LocalPlayer::getLocalPlayerPtr() const
{
    auto& mem = Memory::get();

    auto baseAddr = mem.getBaseAddr("linux_64_client");
    if(!baseAddr) return std::nullopt;

    return mem.readProcess <uintptr_t> (*baseAddr + Offsets::LocalPlayer);
}

std::optional <int> LocalPlayer::getHealth() const
{
    auto localPlayerPtr_opt = getLocalPlayerPtr();

    if(!localPlayerPtr_opt) return std::nullopt;

    auto& mem = Memory::get();

    return mem.readProcess <int> (*localPlayerPtr_opt + Offsets::PlayerStats::healhOffset);
}

std::optional <int> LocalPlayer::getAmmo() const
{
    auto localPlayerPtr_opt = getLocalPlayerPtr();

    if(!localPlayerPtr_opt) return std::nullopt;

    auto& mem = Memory::get();

    return mem.readProcess <int> (*localPlayerPtr_opt + Offsets::PlayerStats::ammoOffset);
}

bool LocalPlayer::setAmmo(const int& value) const
{
    auto localPlayerPtr_opt = getLocalPlayerPtr();

    if(!localPlayerPtr_opt) return false;

    auto& mem = Memory::get();

    return mem.writeProcess <int> (*localPlayerPtr_opt + Offsets::PlayerStats::ammoOffset,value);
}
bool LocalPlayer::setHealth(const int& value) const
{
    auto localPlayerPtr_opt = getLocalPlayerPtr();

    if(!localPlayerPtr_opt) return false;

    auto& mem = Memory::get();

    return mem.writeProcess <int> (*localPlayerPtr_opt + Offsets::PlayerStats::healhOffset,value);
}
