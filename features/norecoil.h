#ifndef NORECOIL_H
#define NORECOIL_H
#include "../sdk/weapon.h"

class NoRecoil
{
public:
    static bool enableNoRecoil(Weapon& weapon, bool enable, int16_t base, const int16_t increment, const int16_t max);
};

#endif // NORECOIL_H
