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
            m_manaMap[ManaType::BLUE]++;
        }

        explicit BlueMana(int amount)
        {
            m_manaMap[ManaType::BLUE] += amount;
        }
    };
} // namespace dandan::mana

#endif // DANDAN_BLUEMANA_H