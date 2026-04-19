#ifndef DANDAN_ANDMANA_H
#define DANDAN_ANDMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class AndMana : public Mana
    {
    public:
        AndMana(const Mana &a, const Mana &b)
        {
            for (const auto &[type, amount] : a.getMana())
            {
                m_manaMap[type] += amount;
            }
            for (const auto &[type, amount] : b.getMana())
            {
                m_manaMap[type] += amount;
            }
        }
    };
} // namespace dandan::mana

#endif // DANDAN_ANDMANA_H