#ifndef DANDAN_MANABAG_H
#define DANDAN_MANABAG_H

#include "dandan/mana/ManaType.h"
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <map>
#include <string>

namespace dandan::mana
{
    /** @brief A collection of mana grouped by mana type.
     * @class ManaBag
     */
    class ManaBag
    {
    public:
        ManaBag() = default;

        /** Constructs a bag from mana type and amount pairs.
         * @param init_list The mana amounts to add to the bag.
         */
        ManaBag(std::initializer_list<std::pair<ManaType, size_t>> init_list);

        /** Gets the amount of a mana type.
         * @param type The mana type to look up.
         * @return The amount of that mana type.
         */
        [[nodiscard]] std::size_t get(ManaType type) const;

        /** Checks whether this bag contains at least the mana in another bag.
         * @param other The mana to look for.
         * @return True if all amounts in other are covered, false otherwise.
         */
        [[nodiscard]] bool contains(const ManaBag &other) const;

        /** Gets the total amount of mana in the bag.
         * @return The total amount of mana.
         */
        [[nodiscard]] size_t total() const;

        /** Subtracts the mana in another bag from a copy of this bag.
         * @param other The mana to subtract.
         * @return A bag containing the remaining mana.
         */
        [[nodiscard]] ManaBag subtract(const ManaBag &other) const;

        /** Subtracts an amount of mana of any type from a copy of this bag.
         * @param amount The amount of mana to subtract.
         * @return A bag containing the remaining mana.
         */
        [[nodiscard]] ManaBag subtractAny(size_t amount) const;

        /** Adds another bag of mana to a copy of this bag.
         * @param other The mana to add.
         * @return A bag containing the combined mana.
         */
        [[nodiscard]] ManaBag add(const ManaBag &other) const;

        /** Checks whether the bag contains no mana.
         * @return True if the bag is empty, false otherwise.
         */
        [[nodiscard]] bool empty() const;

        /** Gets the underlying mana amounts.
         * @return A const reference to the map of mana types to amounts.
         */
        [[nodiscard]] const std::map<ManaType, std::size_t> &data() const;

        /** Converts a mana bag to a symbol string.
         * @param mana The mana bag to convert.
         * @return The mana symbols as a string.
         */
        [[maybe_unused]]
        static std::string ManaToSymbols(const dandan::mana::ManaBag &mana);

        /** Writes a mana bag to an output stream.
         * @param ostream The output stream.
         * @param mana The mana bag to write.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &ostream,
                                        const ManaBag &mana);

    private:
        std::map<ManaType, std::size_t> m_map;
    };
} // namespace dandan::mana

#endif
