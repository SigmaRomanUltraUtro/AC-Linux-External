#ifndef ANTIKNOCKBACK_H
#define ANTIKNOCKBACK_H
#include "../features/modifier.h"
#include <map>

class AntiKnockBack : public Modifier
{
private:
    int16_t modifiedKnockValue = 0;
    std::map<uintptr_t ,int16_t> historyKnock;

public:
    AntiKnockBack(int16_t valueKnock);

    void setKnockValue(int16_t);

    bool update(LocalPlayer& lPlayer, Weapon& weapon) override;
    bool disable(LocalPlayer& lPlayer) override;
    void cfgUpdate(const Setting& config) override;
};

#endif // ANTIKNOCKBACK_H
