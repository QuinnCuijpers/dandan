#ifndef DANDAN_ANDMANA_H
#define DANDAN_ANDMANA_H

#include "Mana.h"
#include <memory>

namespace dandan::mana
{
    /** @brief A class representing the logical AND of two mana resources.
     * @class AndMana
     *
     * @implements Mana
     */
    class AndMana : public Mana
    {
    public:
        /** Constructs an AndMana instance.
         * @param a The first mana resource.
         * @param b The second mana resource.
         */
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
