#pragma once
#include <sys/types.h>
#include <optional>
#include <cstdint>
#include "../memory/memory.h"

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
};