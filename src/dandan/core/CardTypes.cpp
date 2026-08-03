#include "dandan/core/CardTypes.h"
#include <cassert>

namespace dandan::core
{
    std::string_view TypeToString(Type type)
    {
        switch (type)
        {
        case Type::Land:
            return "Land";
        case Type::Creature:
            return "Creature";
        case Type::Sorcery:
            return "Sorcery";
        case Type::Instant:
            return "Instant";
        case Type::Enchantment:
            return "Enchantment";
        case Type::Artifact:
            return "Artifact";
        case Type::Planeswalker:
            return "Planeswalker";
        }
        assert(false && "Unreachable Card type");
    }

    std::string_view SubTypeToString(SubType subtype)
    {
        switch (subtype)
        {
        case SubType::None:
            return "None";
        case SubType::Forest:
            return "Forest";
        case SubType::Island:
            return "Island";
        case SubType::Mountain:
            return "Mountain";
        case SubType::Plains:
            return "Plains";
        case SubType::Swamp:
            return "Swamp";
        case SubType::Fish:
            return "Fish";
        case SubType::Illusion:
            return "Illusion";
        case SubType::Dragon:
            return "Dragon";
        }
        assert(false && "Unreachable Card subtype");
    }
} // namespace dandan::core
