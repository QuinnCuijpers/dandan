#ifndef DANDAN_GENERICMANA_H
#define DANDAN_GENERICMANA_H

#include "Mana.h"

namespace dandan::mana
{

    class GenericMana : public Mana
    {

        GenericMana(int amount)
        {
            m_manaMap[ManaType::GENERIC] += amount;
        }

        ManaMap getMana() const override;
    };
} // namespace dandan::mana

#endif