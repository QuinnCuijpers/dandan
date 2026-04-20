#ifndef DANDAN_ANDMANA_H
#define DANDAN_ANDMANA_H

#include "Mana.h"
#include <memory>

namespace dandan::mana
{
    class AndMana : public Mana
    {
    public:
        AndMana(std::unique_ptr<Mana> a, std::unique_ptr<Mana> b) // NOLINT
        {
            for (const auto &[type, amount] : a->getMana())
            {
                addMana(type, amount);
            }
            for (const auto &[type, amount] : b->getMana())
            {
                addMana(type, amount);
            }
        }
    };
} // namespace dandan::mana

#endif // DANDAN_ANDMANA_H