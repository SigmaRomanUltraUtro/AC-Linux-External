#include "Entity.h"
#include "../Offsets.h"

Entity::Entity(uintptr_t baseAddr) : baseAddr(baseAddr), mem(Memory::get()) {}

std::optional <int> Entity::getHealth() const
{
    if(baseAddr == 0) return std::nullopt;

    return mem.readProcess <int> (baseAddr + offsets::mPlayer::iHealth);
}

bool Entity::setHealth(int value)
{
    if(value <= 0 || baseAddr == 0) return false;

    return mem.writeProcess <int> (baseAddr + offsets::mPlayer::iHealth, value);
}

bool Entity::setArmor(int value)
{
    if(value <= 0 || baseAddr == 0) return false;

    return mem.writeProcess <int> (baseAddr + offsets::mPlayer::iArmor, value);
}

std::optional <int> Entity::getArmor() const
{
    if(baseAddr == 0) return std::nullopt;

    return mem.readProcess <int> (baseAddr + offsets::mPlayer::iArmor);
}

bool Entity::updateBaseAddr(uintptr_t baseAddr)
{
    if(baseAddr != 0)
    {
        this->baseAddr = baseAddr;
        return true;
    }
    return false;
}