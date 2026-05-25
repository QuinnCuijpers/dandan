#ifndef DANDAN_COLORLESSMANA_H
#define DANDAN_COLORLESSMANA_H

#include "Mana.h"

namespace dandan::mana
{
    /** @brief A class representing colorless mana.
     * @class ColorlessMana
     *
     * @implements Mana
     */
    class ColorlessMana : public Mana
    {
    public:
        ColorlessMana()
        {
            addMana(ManaType::COLORLESS, 1);
        }

        /** Constructs a ColorlessMana instance with the specified amount of
         * colorless mana.
         * @param amount The amount of colorless mana to add.
         */
        explicit ColorlessMana(int amount)
        {
            addMana(ManaType::COLORLESS, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_COLORLESSMANA_H
