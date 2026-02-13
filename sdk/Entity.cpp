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

std::optional<Position> Entity::getPosition()
{
    if(baseAddr != 0)
    {
        auto posX_opt = mem.readProcess<float>(baseAddr + offsets::players::fPosX);
        auto posY_opt = mem.readProcess<float>(baseAddr + offsets::players::fPosY);
        auto posZ_opt = mem.readProcess<float>(baseAddr + offsets::players::fPosZ);

        if(posX_opt && posY_opt && posZ_opt)
            return Position{*posX_opt, *posY_opt, *posZ_opt};
    }
    return std::nullopt;
}

bool Entity::setPosition(const Position& pos)
{
    if(!pos.isValid() || baseAddr == 0)
        return false;

    auto posX_opt = mem.writeProcess<float>(baseAddr + offsets::players::fPosX, pos.fPosX);
    auto posY_opt = mem.writeProcess<float>(baseAddr + offsets::players::fPosX, pos.fPosY);
    auto posZ_opt = mem.writeProcess<float>(baseAddr + offsets::players::fPosX, pos.fPosZ);

    return posX_opt && posY_opt && posZ_opt;
}

bool Entity::getInfoDead() const
{
    if(baseAddr == 0)
        return false;

    auto infoDead_opt = mem.readProcess<int>(baseAddr + offsets::players::iDead);

    if(infoDead_opt)
        return *infoDead_opt == 1;

    return false;
}