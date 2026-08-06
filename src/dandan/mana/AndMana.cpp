
#include "dandan/mana/AndMana.h"
namespace dandan::mana
{
    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    AndMana::AndMana(std::unique_ptr<Manapool> first,
                     std::unique_ptr<Manapool> second)
    {
        for (const auto &[type, amount] : first->getMana())
        {
            addMana(type, amount);
        }
        for (const auto &[type, amount] : second->getMana())
        {
            addMana(type, amount);
        }
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)
} // namespace dandan::mana
