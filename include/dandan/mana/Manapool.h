#ifndef DANDAN_MANAPOOL_H
#define DANDAN_MANAPOOL_H

#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaPrice.h"
#include <cassert>
#include <ios>
#include <iostream>

namespace dandan::mana
{

    /** @brief A class representing a manapool in the game.
     * @class Manapool
     */
    class Manapool
    {
    public:
        Manapool() = default;
        Manapool(const Manapool &) = delete;
        Manapool(Manapool &&) = default;
        Manapool &operator=(const Manapool &) = delete;
        Manapool &operator=(Manapool &&) = default;
        virtual ~Manapool() = default;

        /** Adds mana to the resource pool.
         * @param type The type of mana to add.
         * @param amount The amount of mana to add.
         */
        void add(const ManaBag &mana)
        {
            m_manapool = m_manapool.add(mana);
        }

        [[nodiscard]] ManaBag view() const
        {
            return m_manapool;
        }

        /** Checks if the mana can cover the cost passed in.
         * @param price The price to check.
         * @return True if the mana can pay the price, false otherwise.
         */
        [[nodiscard]] bool canPay(const ManaPrice &price) const
        {
            std::cout << "contains: " << std::boolalpha
                      << m_manapool.contains(price.specific()) << '\n';
            if (!m_manapool.contains(price.specific()))
            {
                return false;
            }
            return m_manapool.total() >= price.totalRequired();
        }

        /** Pays the cost of the mana passed in.
         * @param cost The cost to pay.
         */

        bool pay(const ManaPrice &price)
        {
            if (!canPay(price))
            {
                return false;
            }

            ManaBag remaining = m_manapool.subtract(price.specific());

            remaining = remaining.subtractAny(price.generic());

            m_manapool = remaining;
            return true;
        }

        /** Empties the mana pool.
         */
        void empty()
        {
            m_manapool = ManaBag{};
        }

        /** Outputs the mana to an output stream.
         * @param ostream The output stream.
         * @param mana The mana to output.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &ostream,
                                        const Manapool &mana)
        {
            ostream << ManaBag::ManaToSymbols(mana.view());
            return ostream;
        }

    private:
        ManaBag m_manapool{};
    };
} // namespace dandan::mana

#endif // DANDAN_MANA_H
