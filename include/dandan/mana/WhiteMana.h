#ifndef DANDAN_WHITEMANA_H
#define DANDAN_WHITEMANA_H

#include "Mana.h"

namespace dandan::mana
{

    class WhiteMana : public Mana
    {
    public:
        /// Default constructor for creating a WhiteMana with 1 white mana
        WhiteMana()
        {
            addMana(ManaType::WHITE, 1);
        }

        /// Constructor for creating a WhiteMana with a specific amount of white
        /// mana
        explicit WhiteMana(int amount)
        {
            addMana(ManaType::WHITE, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_WHITEMANA_H