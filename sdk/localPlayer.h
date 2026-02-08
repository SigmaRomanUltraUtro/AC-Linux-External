#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include <sys/types.h>
#include <optional>
#include <cstdint>
#include "../memory/memory.h"

class LocalPlayer
{
public:
    LocalPlayer();

    bool update(uintptr_t baseAddr);

    std::optional <int> getHealth() const;

    bool setHealth(int value);

    std::optional <int> getArrmor() const;

    bool setArrmor(int value);

    std::optional <uintptr_t> getWeaponPtr() const;

private:

    Memory& mem;
    uintptr_t localPlayerAddr;
};

#endif // LOCALPLAYER_H
