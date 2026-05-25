#ifndef DANDAN_MANALIST_H
#define DANDAN_MANALIST_H

#include "Mana.h"
#include <memory>
#include <vector>

namespace dandan::mana
{
    /** A class representing a list of different mana options
     * @class ManaList
     */
    class ManaList
    {
    public:
        /** Constructs a ManaList instance with the specified mana option.
         * @param mana The mana option to add.
         */
        explicit ManaList(std::unique_ptr<Mana> mana)
        {
            m_options.push_back(std::move(mana));
        }
        /** Constructs a ManaList instance with the specified mana options.
         * @param options The mana options to add.
         */
        explicit ManaList(std::vector<std::unique_ptr<Mana>> options)
            : m_options{std::move(options)}
        {
        }

        /** Returns the list of mana options.
         * @returns The list of mana options.
         */
        [[nodiscard]] const std::vector<std::unique_ptr<Mana>> &getOptions()
            const
        {
            return m_options;
        }

    private:
        std::vector<std::unique_ptr<Mana>> m_options;
    };
} // namespace dandan::mana

#endif // DANDAN_MANALIST_H