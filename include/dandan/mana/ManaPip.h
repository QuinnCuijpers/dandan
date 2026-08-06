#ifndef DANDAN_COLOREDMANA_H
#define DANDAN_COLOREDMANA_H

#include "Manapool.h"
#include "dandan/mana/ManaType.h"

namespace dandan::mana
{
    template <ManaType type> class ManaPip : public Manapool
    {
    public:
        ManaPip()
        {
            addMana(type, 1);
        }

        explicit ManaPip(int amount)
        {
            addMana(type, amount);
        }
    };

    using BlueMana = mana::ManaPip<mana::ManaType::BLUE>;
    using RedMana = mana::ManaPip<mana::ManaType::RED>;
    using WhiteMana = mana::ManaPip<mana::ManaType::WHITE>;
    using BlackMana = mana::ManaPip<mana::ManaType::BLACK>;
    using GreenMana = mana::ManaPip<mana::ManaType::GREEN>;
    using GenericMana = mana::ManaPip<mana::ManaType::GENERIC>;
    using ColorlessMana = mana::ManaPip<mana::ManaType::COLORLESS>;

} // namespace dandan::mana

#endif
