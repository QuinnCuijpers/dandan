#ifndef DANDAN_ANDMANA_H
#define DANDAN_ANDMANA_H

#include "Manapool.h"
#include <memory>

namespace dandan::mana
{
    /** @brief A class representing the logical AND of two mana resources.
     * @class AndMana
     *
     * @implements Mana
     */
    class AndMana : public Manapool
    {
    public:
        /** Constructs an AndMana instance.
         * @param a The first mana resource.
         * @param b The second mana resource.
         */
        AndMana(std::unique_ptr<Manapool> first,
                std::unique_ptr<Manapool> second);
    };
} // namespace dandan::mana

#endif // DANDAN_ANDMANA_H
