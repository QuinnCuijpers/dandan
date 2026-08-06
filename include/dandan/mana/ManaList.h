#ifndef DANDAN_MANALIST_H
#define DANDAN_MANALIST_H

#include "Manapool.h"
#include <memory>
#include <vector>

namespace dandan::mana
{
    /** @brief A class representing a list of different mana options
     * @class ManaList
     */
    class ManaList
    {
    public:
        /** Constructs a ManaList instance with the specified mana option.
         * @param mana The mana option to add.
         */
        explicit ManaList(std::unique_ptr<Manapool> mana);

        /** Constructs a ManaList instance with the specified mana options.
         * @param options The mana options to add.
         */
        explicit ManaList(std::vector<std::unique_ptr<Manapool>> options);

        /** Returns the list of mana options.
         * @returns The list of mana options.
         */
        [[nodiscard]] const std::vector<std::unique_ptr<Manapool>> &getOptions()
            const;

    private:
        std::vector<std::unique_ptr<Manapool>> m_options;
    };
} // namespace dandan::mana

#endif // DANDAN_MANALIST_H
