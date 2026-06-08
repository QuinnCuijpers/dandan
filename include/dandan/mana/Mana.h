#ifndef DANDAN_MANA_H
#define DANDAN_MANA_H

#include "dandan/mana/ManaType.h"
#include <cassert>
#include <map>
#include <string>

namespace dandan::mana
{

    using ManaMap = std::map<ManaType, int>;

    [[maybe_unused]]
    static std::string ManaToSymbols(const ManaMap &mana_map)
    {
        if (mana_map.empty())
        {
            return "(0)";
        }

        std::string symbols{};
        std::string generic_part{};
        for (const auto &[mana_type, amount] : mana_map)
        {
            std::string symbol{};
            switch (mana_type)
            {
            case ManaType::COLORLESS:
                symbol = "C";
                break;
            case ManaType::WHITE:
                symbol = "W";
                break;
            case ManaType::BLUE:
                symbol = "U";
                break;
            case ManaType::BLACK:
                symbol = "B";
                break;
            case ManaType::RED:
                symbol = "R";
                break;
            case ManaType::GREEN:
                symbol = "G";
                break;
            case ManaType::GENERIC:
                generic_part = "(" + std::to_string(amount) + ")";
                continue;
            default:
                symbol = "?";
                break;
            }
            for (int i = 0; i < amount; ++i)
            {
                symbols += symbol;
            }
        }

        if (symbols.empty())
        {
            return generic_part;
        }
        if (generic_part == "(0)" && !symbols.empty())
        {
            return symbols;
        }
        return generic_part + symbols;
    }

    inline std::ostream &operator<<(std::ostream &ostream,
                                    const ManaMap &mana_map)
    {
        ostream << ManaToSymbols(mana_map);
        return ostream;
    }

    /** @brief A class representing mana in the game.
     * @class Mana
     */
    class Mana
    {
    public:
        Mana() = default;
        Mana(const Mana &) = delete;
        Mana(Mana &&) = delete;
        Mana &operator=(const Mana &) = delete;
        Mana &operator=(Mana &&) = delete;
        virtual ~Mana() = default;

        /** Adds mana to the resource pool.
         * @param type The type of mana to add.
         * @param amount The amount of mana to add.
         */
        virtual void addMana(ManaType type, int amount)
        {
            m_manaMap[type] += amount;
        }

        /** Retrieves the underlying mana map mutably.
         * @return A reference to the mana map.
         */
        [[nodiscard]] virtual ManaMap &getMana()
        {
            return m_manaMap;
        }

        /** Retrieves the underlying mana map.
         * @return A const reference to the mana map.
         */
        [[nodiscard]] virtual const ManaMap &getMana() const
        {
            return m_manaMap;
        };

        /** Checks if the mana can cover the cost passed in.
         * @param cost The cost to check.
         * @return True if the mana can pay the cost, false otherwise.
         */
        [[nodiscard]] bool canPay(const Mana &cost) const
        {
            int generic_cost = cost.getMana().at(ManaType::GENERIC);
            int available_generic{};
            for (const auto &[type, amount] : cost.getMana())
            {
                if (type == ManaType::GENERIC)
                {
                    continue;
                }
                if (m_manaMap.at(type) < amount)
                {
                    return false;
                }
                available_generic += m_manaMap.at(type) - amount;
            }
            return available_generic >= generic_cost;
        }

        /** Pays the cost of the mana passed in.
         * @param cost The cost to pay.
         */
        void pay(const Mana &cost)
        {
            int generic_cost = cost.getMana().at(ManaType::GENERIC);

            // TODO: generic mana is now paid by draining colors in order, which
            // is not how it works in MTG. Fix this by allowing the caller to
            // specify how to pay generic mana
            for (const auto &[type, amount] : cost.getMana())
            {
                if (type == ManaType::GENERIC)
                {
                    continue;
                }
                m_manaMap[type] -= amount;
                if (m_manaMap[type] > 0)
                {
                    m_manaMap[type] -= std::min(m_manaMap[type], generic_cost);
                }
            }
        }

        /** Empties the mana pool.
         */
        void empty()
        {
            for (auto &[type, amount] : m_manaMap)
            {
                amount = 0;
            }
        }

        /** Outputs the mana to an output stream.
         * @param ostream The output stream.
         * @param mana The mana to output.
         * @return The output stream.
         */
        friend std::ostream &operator<<(std::ostream &ostream, const Mana &mana)
        {
            ostream << ManaToSymbols(mana.getMana());
            return ostream;
        }

    private:
        ManaMap m_manaMap{
            {ManaType::COLORLESS, 0}, {ManaType::WHITE, 0},
            {ManaType::BLUE, 0},      {ManaType::BLACK, 0},
            {ManaType::RED, 0},       {ManaType::GREEN, 0},
            {ManaType::GENERIC, 0},
        };
    };

} // namespace dandan::mana

#endif // DANDAN_MANA_H
