#ifndef DANDAN_COLORLESSMANA_H
#define DANDAN_COLORLESSMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class ColorlessMana : public Mana
    {
    public:
        ColorlessMana()
        {
            m_manaMap[ManaType::COLORLESS]++;
        }
    };
} // namespace dandan::mana

#endif // DANDAN_COLORLESSMANA_H