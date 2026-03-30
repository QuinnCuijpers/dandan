#include "dandan/abilities/ReplacementAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::abilities
{

    void ReplacementAbility::resolve()
    {
        std::cout << "Resolving ReplacementAbility\n";
    }

    void ReplacementAbility::from_json(const nlohmann::json &j, IAbility &ability)
    {
        // This is a placeholder implementation. In a real implementation, you would need to deserialize the event type and the replacement effect.
        // For example, you might have a mapping of event types to their corresponding classes, and similarly for replacement effects.
        // You would then use this mapping to create the appropriate instances based on the JSON data.
    }

    void ReplacementAbility::to_json(nlohmann::json &j, const IAbility &ability)
    {

        const auto &replacementAbility = dynamic_cast<const ReplacementAbility &>(ability);
        j = nlohmann::json{{"type", "ReplacementAbility"}, {"data", nlohmann::json()}};

        j["data"]["event"] = nlohmann::json();
        replacementAbility.m_event->to_json(j["data"]["event"], *replacementAbility.m_event);

        j["data"]["replacement_effect"] = nlohmann::json();
        replacementAbility.m_replace_effect->to_json(j["data"]["replacement_effect"], *replacementAbility.m_replace_effect);
    }
}