#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include <sys/types.h>
#include <optional>
#include <cstdint>

class LocalPlayer
{
public:
    std::optional <int> getHealth() const;

    bool setHealth(const int& value) const;

    std::optional <int> getArrmor() const;

    bool setArrmor(const int& value) const;

    std::optional <uintptr_t> getPlayerPtr() const;

    bool update();

    uintptr_t getPlayerAddr() const;

    std::optional <uintptr_t> getWeaponPtr() const;

private:

    uintptr_t localPlayerAddr;
};

#endif // LOCALPLAYER_H
