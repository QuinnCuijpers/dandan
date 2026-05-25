#ifndef DANDAN_GREENMANA_H
#define DANDAN_GREENMANA_H

#include "Mana.h"

namespace dandan::mana
{
    /** @brief A class representing green mana.
     * @class GreenMana
     *
     * @implements Mana
     */
    class GreenMana : public Mana
    {
    public:
        GreenMana()
        {
            addMana(ManaType::GREEN, 1);
        }

        /** Constructs a GreenMana instance with the specified amount of green
         * mana.
         * @param amount The amount of green mana to add.
         */
        explicit GreenMana(int amount)
        {
            addMana(ManaType::GREEN, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_GREENMANA_H
