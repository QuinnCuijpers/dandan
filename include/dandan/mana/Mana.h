#ifndef DANDAN_MANA_H
#define DANDAN_MANA_H

#include <map>
#include <stdexcept>
#include <string>
#include <string_view>

namespace dandan::mana
{

    enum class ManaType
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
        default:
            return "Unknown";
        }
    }

    [[maybe_unused]]
    static ManaType ManaTypeFromString(const std::string_view &str)
    {
        if (str == "Colorless")
            return ManaType::COLORLESS;
        else if (str == "White")
            return ManaType::WHITE;
        else if (str == "Blue")
            return ManaType::BLUE;
        else if (str == "Black")
            return ManaType::BLACK;
        else if (str == "Red")
            return ManaType::RED;
        else if (str == "Green")
            return ManaType::GREEN;
        else if (str == "Generic")
            return ManaType::GENERIC;
        else
            throw std::invalid_argument("Invalid mana type string: " +
                                        std::string(str));
    }

    typedef std::map<ManaType, int> ManaMap;

    class Mana
    {
    public:
        virtual ~Mana() = default;
        virtual ManaMap getMana() const
        {
            return m_manaMap;
        };

    protected:
        ManaMap m_manaMap;
    };

    [[maybe_unused]]
    static std::string ManaToSymbols(const ManaMap &mana_map)
    {
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
} // namespace dandan::mana

#endif // DANDAN_MANA_H