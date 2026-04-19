#ifndef DANDAN_BLACKMANA_H
#define DANDAN_BLACKMANA_H

#include "Mana.h"

namespace dandan::mana
{

    class BlackMana : public Mana
    {
    public:
        BlackMana()
        {
            m_manaMap[ManaType::BLACK]++;
        }
    };

} // namespace dandan::mana

#endif // DANDAN_BLACKMANA_H