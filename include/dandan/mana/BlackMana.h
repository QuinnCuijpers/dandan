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
            addMana(ManaType::BLACK, 1);
        }
        explicit BlackMana(int amount)
        {
            addMana(ManaType::BLACK, amount);
        }
    };

} // namespace dandan::mana

#endif // DANDAN_BLACKMANA_H