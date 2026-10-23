#include "dandan/core/TargetRequirement.h"

namespace dandan::core
{
    std::string targetTypeToString(TargetType target_type)
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

    std::ostream &operator<<(std::ostream &ostream, TargetType target_type)
    {
        return ostream << targetTypeToString(target_type);
    }

    TargetSpec::TargetSpec(std::vector<TargetType> types, Controller controller)
        : types(std::move(types)), controller(controller)
    {
    }

    TargetSpec::TargetSpec(std::vector<TargetType> types,
                           const std::string &key, Controller controller)
        : types(std::move(types)), controller(controller),
          source(TargetSource::Linked), key(key)
    {
    }

    TargetRequirement::TargetRequirement(
        const std::vector<TargetSpec> &target_types)
        : m_targets(target_types)
    {
    }

    TargetRequirement::TargetRequirement(
        const std::vector<std::vector<TargetType>> &target_types)
    {
        m_targets.reserve(target_types.size());
        std::transform(target_types.begin(), target_types.end(),
                       std::back_inserter(m_targets),
                       [](const std::vector<TargetType> &target_type)
                       { return TargetSpec{target_type}; });
    }

    const std::vector<TargetSpec> &TargetRequirement::getTargetTypes() const
    {
        return m_targets;
    }
} // namespace dandan::core
