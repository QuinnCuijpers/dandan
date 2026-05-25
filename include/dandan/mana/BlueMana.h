#ifndef DANDAN_BLUEMANA_H
#define DANDAN_BLUEMANA_H

#include "Mana.h"

namespace dandan::mana
{
    /** A class representing blue mana.
     * @class BlueMana
     *
     * @implements Mana
     */
    class BlueMana : public Mana
    {
    public:
        /** Constructs a BlueMana instance.
         * @param amount The amount of blue mana.
         */
        BlueMana()
        {
            addMana(ManaType::BLUE, 1);
        }

        explicit BlueMana(int amount)
        {
            addMana(ManaType::BLUE, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_BLUEMANA_H