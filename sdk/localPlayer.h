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

    bool update();

    std::optional <int> getHealth() const;

    bool setHealth(const int& value) const;

    std::optional <int> getArrmor() const;

    bool setArrmor(const int& value) const;

    std::optional <uintptr_t> getWeaponPtr() const;

private:

    Memory& mem;
    uintptr_t localPlayerAddr;
};

#endif // LOCALPLAYER_H
