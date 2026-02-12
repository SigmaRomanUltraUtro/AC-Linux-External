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

    std::optional<float> getPitch() const;

    bool setPitch(float degreesValue);

    std::optional<float> getYaw() const;

    bool setYaw(float deareesValue);

    std::optional <int> getHealth() const;

    bool setHealth(int value);

    std::optional <int> getArmor() const;

    bool setArmor(int value);

    std::optional <uintptr_t> getWeaponPtr() const;

private:

    Memory& mem;
    uintptr_t localPlayerAddr;
};

#endif // LOCALPLAYER_H
