#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H
#include <sys/types.h>
#include "Entity.h"

class LocalPlayer : public Entity
{
public:
 LocalPlayer(uintptr_t baseAddr);

 std::optional<float> getPitch() const;

 bool setPitch(float degreesValue);

 std::optional<float> getYaw() const;

 bool setYaw(float deareesValue);

 std::optional<uintptr_t> getWeaponPtr() const;
};

#endif // LOCALPLAYER_H
