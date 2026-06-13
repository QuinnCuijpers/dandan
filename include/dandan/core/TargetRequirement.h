#ifndef DANDAN_TARGETREQUIREMENT_H
#define DANDAN_TARGETREQUIREMENT_H

#include <cstdint>
#include <ostream>
#include <vector>
namespace dandan::core
{

    enum class TargetType : int8_t
    {
        Player,
        Creature,
        Land,
        Permanent,
        Spell,
        Planeswalker,
        Card,
        Any
    };

    inline std::string targetTypeToString(TargetType target_type)
    {
        switch (target_type)
        {
        case TargetType::Player:
            return "Player";
        case TargetType::Creature:
            return "Creature";
        case TargetType::Permanent:
            return "Permanent";
        case TargetType::Land:
            return "Land";
        case TargetType::Planeswalker:
            return "Planeswalker";
        case TargetType::Spell:
            return "Spell";
        case TargetType::Card:
            return "Card";
        case TargetType::Any:
            return "Any";
        default:
            return "Unknown";
        }
    }

    inline std::ostream &operator<<(std::ostream &ostream,
                                    TargetType target_type)
    {
        return ostream << targetTypeToString(target_type);
    }

    class TargetRequirement
    {
    public:
        explicit TargetRequirement(
            std::vector<std::vector<TargetType>> target_types)
            : m_target_types(std::move(target_types))
        {
        }

        [[nodiscard]] const std::vector<std::vector<TargetType>> &
        getTargetTypes() const
        {
            return m_target_types;
        }

    private:
        std::vector<std::vector<TargetType>> m_target_types;
    };
} // namespace dandan::core

#endif