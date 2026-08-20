#ifndef DANDAN_MANALIST_H
#define DANDAN_MANALIST_H

#include "dandan/mana/ManaBag.h"
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
        explicit ManaList(ManaBag mana);

        /** Constructs a ManaList instance with the specified mana options.
         * @param options The mana options to add.
         */
        explicit ManaList(std::vector<ManaBag> options);

        /** Returns the list of mana options.
         * @returns The list of mana options.
         */
        [[nodiscard]] const std::vector<ManaBag> &getOptions() const;

    private:
        std::vector<ManaBag> m_options;
    };
} // namespace dandan::mana

#endif // DANDAN_MANALIST_H
