#ifndef DANDAN_TARGETREQUIREMENT_H
#define DANDAN_TARGETREQUIREMENT_H

#include <cstdint>
#include <optional>
#include <ostream>
#include <utility>
#include <vector>
namespace dandan::core
{

    enum class TargetType : uint8_t
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

    enum class Controller : uint8_t
    {
        You,
        Opponent,
        Any,
    };

    enum class TargetSource : uint8_t
    {
        Prompt,
        Linked,
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

    struct TargetSpec
    {
        std::vector<TargetType> types;
        Controller controller{Controller::Any};
        TargetSource source{TargetSource::Prompt};
        std::optional<std::string> key;

        TargetSpec(std::vector<TargetType> types,
                   Controller controller = Controller::Any)
            : types(std::move(types)), controller(controller)
        {
        }

        TargetSpec(std::vector<TargetType> types, std::string key,
                   Controller controller = Controller::Any)
            : types(std::move(types)), controller(controller),
              source(TargetSource::Linked), key(key)
        {
        }
    };

    class TargetRequirement
    {
    public:
        explicit TargetRequirement(const std::vector<TargetSpec> &target_types)
            : m_targets(target_types)
        {
        }

        explicit TargetRequirement(
            const std::vector<std::vector<TargetType>> &target_types)
        {
            for (const auto &target_type : target_types)
            {
                m_targets.emplace_back(target_type);
            }
        }

        [[nodiscard]] const std::vector<TargetSpec> &getTargetTypes() const
        {
            return m_targets;
        }

    private:
        std::vector<TargetSpec> m_targets;
    };
} // namespace dandan::core

#endif