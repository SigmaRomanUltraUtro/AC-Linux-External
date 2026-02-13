#pragma once
#include <sys/types.h>
#include <optional>
#include <cstdint>
#include "../memory/memory.h"

struct Position
{
    float fPosX = 0;
    float fPosY = 0;
    float fPosZ = 0;

    bool isValid() const
    {
        return fPosX > 0 && fPosY > 0 && fPosZ > 0;
    }
};

class Entity
{
protected:
 uintptr_t baseAddr = 0;
 Memory& mem;

public:
 Entity(uintptr_t baseAddr);

 bool updateBaseAddr(uintptr_t baseAddr);

 std::optional<int> getHealth() const;

 bool setHealth(int value);

 std::optional<int> getArmor() const;

 bool setArmor(int value);

 std::optional<Position> getPosition();

 bool setPosition(const Position& pos);

 bool getInfoDead() const;
};