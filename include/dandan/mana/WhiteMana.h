#ifndef DANDAN_WHITEMANA_H
#define DANDAN_WHITEMANA_H

#include "Mana.h"

namespace dandan::mana
{
    /** A class representing white mana.
     * @class WhiteMana
     *
     * @implements Mana
     */
    class WhiteMana : public Mana
    {
    public:
        WhiteMana()
        {
            addMana(ManaType::WHITE, 1);
        }

        /** Constructs a WhiteMana instance with the specified amount of white
         * mana.
         * @param amount The amount of white mana to add.
         */
        explicit WhiteMana(int amount)
        {
            addMana(ManaType::WHITE, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_WHITEMANA_H