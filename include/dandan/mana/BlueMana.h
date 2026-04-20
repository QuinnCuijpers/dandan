#ifndef DANDAN_BLUEMANA_H
#define DANDAN_BLUEMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class BlueMana : public Mana
    {
    public:
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