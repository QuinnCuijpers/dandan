#ifndef DANDAN_GREENMANA_H
#define DANDAN_GREENMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class GreenMana : public Mana
    {
    public:
        GreenMana()
        {
            addMana(ManaType::GREEN, 1);
        }
        explicit GreenMana(int amount)
        {
            addMana(ManaType::GREEN, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_GREENMANA_H