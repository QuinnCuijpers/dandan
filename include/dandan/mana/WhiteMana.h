#ifndef DANDAN_WHITEMANA_H
#define DANDAN_WHITEMANA_H

#include "Mana.h"

namespace dandan::mana
{
    class WhiteMana : public Mana
    {
    public:
        WhiteMana()
        {
            m_manaMap[ManaType::WHITE]++;
        }
        ManaMap getMana() const override;
    };
} // namespace dandan::mana

#endif // DANDAN_WHITEMANA_H