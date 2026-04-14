#include "dandan/abilities/ManaAbility.h"
#include <iostream>
#include <nlohmann/json.hpp>

namespace dandan::abilities
{

    void ManaAbility::resolve() const
    {
        std::cout << "Resolving ManaAbility: " << ManaTypeToString(m_color)
                  << " mana\n";
    }

    NLOHMANN_JSON_SERIALIZE_ENUM(ManaAbility::ManaType,
                                 {{ManaAbility::ManaType::COLORLESS,
                                   "Colorless"},
                                  {ManaAbility::ManaType::WHITE, "White"},
                                  {ManaAbility::ManaType::BLUE, "Blue"},
                                  {ManaAbility::ManaType::BLACK, "Black"},
                                  {ManaAbility::ManaType::RED, "Red"},
                                  {ManaAbility::ManaType::GREEN, "Green"}})

    std::string_view ManaAbility::ManaTypeToString(ManaType type)
    {
        switch (type)
        {
        case COLORLESS:
            return "Colorless";
        case WHITE:
            return "White";
        case BLUE:
            return "Blue";
        case BLACK:
            return "Black";
        case RED:
            return "Red";
        case GREEN:
            return "Green";
        default:
            return "Unknown";
        }
    }

    ManaAbility::ManaType ManaAbility::ManaTypeFromString(
        const std::string_view &str)
    {
        if (str == "Colorless")
            return COLORLESS;
        else if (str == "White")
            return WHITE;
        else if (str == "Blue")
            return BLUE;
        else if (str == "Black")
            return BLACK;
        else if (str == "Red")
            return RED;
        else if (str == "Green")
            return GREEN;
        else
            throw std::runtime_error("Invalid mana type string: " +
                                     std::string(str));
    }
} // namespace dandan::abilities