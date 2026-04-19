#ifndef DANDAN_GREENMANA_H
#define DANDAN_GREENMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class GreenMana : public Mana
    {
    public:
        GreenMana()
        {
            m_manaMap[ManaType::GREEN]++;
        }
    };
} // namespace dandan::mana

#endif // DANDAN_GREENMANA_H