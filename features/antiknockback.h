#ifndef ANTIKNOCKBACK_H
#define ANTIKNOCKBACK_H
#include "../sdk/weapon.h"

class AntiKnockBack
{
public:
    static bool enebleAntiKnockBack(Weapon& weapon,bool enable, int16_t knockBackValue);
};

#endif // ANTIKNOCKBACK_H
