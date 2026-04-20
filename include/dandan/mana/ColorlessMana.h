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
            addMana(ManaType::COLORLESS, 1);
        }
        explicit ColorlessMana(int amount)
        {
            addMana(ManaType::COLORLESS, amount);
        }
    };
} // namespace dandan::mana

#endif // DANDAN_COLORLESSMANA_H