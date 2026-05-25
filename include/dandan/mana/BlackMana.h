#ifndef DANDAN_BLACKMANA_H
#define DANDAN_BLACKMANA_H

#include "Mana.h"

namespace dandan::mana
{
    /** A class representing black mana.
     * @class BlackMana
     *
     * @implements Mana
     */
    class BlackMana : public Mana
    {
    public:
        BlackMana()
        {
            addMana(ManaType::BLACK, 1);
        }

        /** Constructs a BlackMana instance with the specified amount of black
         * mana.
         * @param amount The amount of black mana to add.
         */
        explicit BlackMana(int amount)
        {
            addMana(ManaType::BLACK, amount);
        }
    };

} // namespace dandan::mana

#endif // DANDAN_BLACKMANA_H