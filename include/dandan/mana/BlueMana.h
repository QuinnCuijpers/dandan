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
        ManaMap getMana() const override
        {
            return m_manaMap;
        }
    };
} // namespace dandan::mana

#endif // DANDAN_BLUEMANA_H