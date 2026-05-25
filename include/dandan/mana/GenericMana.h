#ifndef DANDAN_GENERICMANA_H
#define DANDAN_GENERICMANA_H

#include "Mana.h"

namespace dandan::mana
{
    /** A class representing generic mana.
     * @class GenericMana
     * @implements Mana
     */
    class GenericMana : public Mana
    {
    public:
        /** Constructs a GenericMana instance with the specified amount of
         * generic mana.
         * @param amount The amount of generic mana to add.
         */
        explicit GenericMana(int amount)
        {
            addMana(ManaType::GENERIC, amount);
        }
    };
} // namespace dandan::mana

#endif