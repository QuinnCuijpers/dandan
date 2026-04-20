#ifndef DANDAN_GENERICMANA_H
#define DANDAN_GENERICMANA_H

#include "Mana.h"

namespace dandan::mana
{

    class GenericMana : public Mana
    {
    public:
        explicit GenericMana(int amount)
        {
            addMana(ManaType::GENERIC, amount);
        }
    };
} // namespace dandan::mana

#endif