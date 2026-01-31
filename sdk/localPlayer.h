#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H
#include <sys/types.h>
#include "../Offsets.h"
#include "../memory/memory.h"
#include <cstdint>
class LocalPlayer
{
public:
    LocalPlayer(const pid_t& pid,const uintptr_t& baseAddr) : pid(pid), baseAddr(baseAddr), mem(pid) {}
    int getHealth() const
    {
        return mem.readProcess <uintptr_t> (getLocalPlayerPtr() + Offsets::PlayerStats::HealhOffset);
    }

    bool setHealth(const int& value)
    {
        return mem.writeProcess <int> (getLocalPlayerPtr() + Offsets::PlayerStats::HealhOffset, value);
    }


private:
    uintptr_t getLocalPlayerPtr() const
    {
        return mem.readProcess <uintptr_t> (baseAddr + Offsets::LocalPlayer);
    }
private:

    memory mem;
    uintptr_t baseAddr;
    pid_t pid;
};

#endif // LOCALPLAYER_H
