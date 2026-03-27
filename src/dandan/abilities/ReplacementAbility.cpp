#include "dandan/abilities/ReplacementAbility.h"
#include <nlohmann/json.hpp>

namespace dandan::abilities
{

    void ReplacementAbility::resolve()
    {
        // This ability doesn't resolve in the traditional sense, as it modifies events rather than triggering on them.
        // The actual replacement logic is handled in the event processing system, where the replace method of the IReplacementEffect is called.
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