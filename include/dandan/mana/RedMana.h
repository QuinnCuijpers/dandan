#ifndef DANDAN_REDMANA_H
#define DANDAN_REDMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class RedMana : public Mana
    {
    public:
        RedMana()
        {
            m_manaMap[ManaType::RED]++;
        }
    };
} // namespace dandan::mana

#endif // DANDAN_REDMANA_H