#ifndef DANDAN_MANA_H
#define DANDAN_MANA_H

#include <cassert>
#include <cstdint>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>

namespace dandan::mana
{

    enum class ManaType : std::uint8_t
    {
        COLORLESS,
        WHITE,
        BLUE,
        BLACK,
        RED,
        GREEN,
        GENERIC,
    };

    [[maybe_unused]]
    static std::string_view ManaTypeToString(ManaType type)
    {
        switch (type)
        {
        case ManaType::COLORLESS:
            return "Colorless";
        case ManaType::WHITE:
            return "White";
        case ManaType::BLUE:
            return "Blue";
        case ManaType::BLACK:
            return "Black";
        case ManaType::RED:
            return "Red";
        case ManaType::GREEN:
            return "Green";
        case ManaType::GENERIC:
            return "Generic";
        }

        assert(false && "Unknown mana type in ManaTypeToString");
    }

    [[maybe_unused]]
    static ManaType ManaTypeFromString(const std::string_view &str)
    {
        if (str == "Colorless")
        {
            return ManaType::COLORLESS;
        }
        if (str == "White")
        {
            return ManaType::WHITE;
        }
        if (str == "Blue")
        {
            return ManaType::BLUE;
        }
        if (str == "Black")
        {
            return ManaType::BLACK;
        }
        if (str == "Red")
        {
            return ManaType::RED;
        }
        if (str == "Green")
        {
            return ManaType::GREEN;
        }
        if (str == "Generic")
        {
            return ManaType::GENERIC;
        }
        throw std::invalid_argument("Invalid mana type string: " +
                                    std::string(str));
    }

    using ManaMap = std::map<ManaType, int>;

    [[maybe_unused]]
    static std::string ManaToSymbols(const ManaMap &mana_map)
    {
        if (mana_map.empty())
        {
            return "(0)";
        }

        std::string symbols;
        for (const auto &[mana_type, amount] : mana_map)
        {
            std::string_view symbol{};
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
                if (amount == 0 && !symbols.empty())
                {
                    break;
                }
                symbols += "(" + std::to_string(amount) + ")";
                continue;
            default:
                symbol = "?";
                break;
            }
            for (int i = 0; i < amount; ++i)
            {
                symbols += std::string(symbol);
            }
        }
        return symbols;
    }

    inline std::ostream &operator<<(std::ostream &ostream,
                                    const ManaMap &mana_map)
    {
        ostream << ManaToSymbols(mana_map);
        return ostream;
    }

    class Mana
    {
    public:
        Mana() = default;
        Mana(const Mana &) = delete;
        Mana(Mana &&) = delete;
        Mana &operator=(const Mana &) = delete;
        Mana &operator=(Mana &&) = delete;
        virtual ~Mana() = default;

        virtual void addMana(ManaType type, int amount)
        {
            m_manaMap[type] += amount;
        }

        [[nodiscard]] virtual ManaMap &getMana()
        {
            return m_manaMap;
        }

        [[nodiscard]] virtual const ManaMap &getMana() const
        {
            return m_manaMap;
        };

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

        void pay(const Mana &cost)
        {
            // if (!canPay(cost))
            // {
            //     throw std::runtime_error("Cannot pay mana cost");
            // }

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