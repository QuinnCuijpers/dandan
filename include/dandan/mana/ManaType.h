#ifndef DANDAN_MANATYPE_H
#define DANDAN_MANATYPE_H

#include <cassert>
#include <cstdint>
#include <stdexcept>
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

    // [[maybe_unused]]
    // static std::string_view ManaTypeToString(ManaType type)
    // {
    //     switch (type)
    //     {
    //     case ManaType::COLORLESS:
    //         return "Colorless";
    //     case ManaType::WHITE:
    //         return "White";
    //     case ManaType::BLUE:
    //         return "Blue";
    //     case ManaType::BLACK:
    //         return "Black";
    //     case ManaType::RED:
    //         return "Red";
    //     case ManaType::GREEN:
    //         return "Green";
    //     case ManaType::GENERIC:
    //         return "Generic";
    //     }

    //     assert(false && "Unknown mana type in ManaTypeToString");
    // }

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
        throw std::invalid_argument(std::string("Invalid mana type string: ") +
                                    std::string(str));
    }

} // namespace dandan::mana

#endif