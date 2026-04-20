#ifndef DANDAN_REDMANA_H
#define DANDAN_REDMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class RedMana : public Mana
    {
    public:
        RedMana()
        {
            addMana(ManaType::RED, 1);
        }
        explicit RedMana(int amount)
        {
            addMana(ManaType::RED, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_REDMANA_H