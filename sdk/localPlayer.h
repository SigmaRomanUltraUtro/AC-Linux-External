#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H
#include <sys/types.h>
#include "../Offsets.h"
#include "../memory/memory.h"
#include <cstdint>
class LocalPlayer
{
public:
    std::optional <int> getHealth() const;

    bool setHealth(const int& value) const;

    std::optional <int> getAmmo() const;

    bool setAmmo(const int& value) const;

private:
    std::optional <uintptr_t> getLocalPlayerPtr() const;
private:

    uintptr_t localPlayerAddr;
};

#endif // LOCALPLAYER_H
