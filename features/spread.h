#ifndef SPREAD_H
#define SPREAD_H
#include "../sdk/weapon.h"

class Spread
{
public:
    static bool enableNoSpread(Weapon& weapon,bool enable, int16_t spreadValue);
};

#endif // SPREAD_H
