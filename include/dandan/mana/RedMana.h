#ifndef DANDAN_REDMANA_H
#define DANDAN_REDMANA_H

#include "Mana.h"

namespace dandan::mana
{
    /** A class representing red mana.
     * @class RedMana
     *
     * @implements Mana
     */
    class RedMana : public Mana
    {
    public:
        RedMana()
        {
            addMana(ManaType::RED, 1);
        }

        /** Constructs a RedMana instance with the specified amount of red
         * mana.
         * @param amount The amount of red mana to add.
         */
        explicit RedMana(int amount)
        {
            addMana(ManaType::RED, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_REDMANA_H