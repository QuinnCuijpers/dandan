#ifndef DANDAN_WHITEMANA_H
#define DANDAN_WHITEMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class WhiteMana : public Mana
    {
    public:
        WhiteMana()
        {
            addMana(ManaType::WHITE, 1);
        }
        explicit WhiteMana(int amount)
        {
            addMana(ManaType::WHITE, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_WHITEMANA_H