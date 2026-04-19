#ifndef DANDAN_GENERICMANA_H
#define DANDAN_GENERICMANA_H

#include "Mana.h"

namespace dandan::mana
{

    class GenericMana : public Mana
    {
    public:
        explicit GenericMana(int amount)
        {
            m_manaMap[ManaType::GENERIC] += amount;
        }
    };
} // namespace dandan::mana

#endif