#include "dandan/abilities/TriggeredAbility.h"
#include <nlohmann/json.hpp>

namespace dandan::abilities
{

    void TriggeredAbility::resolve()
    {
        // In a real implementation, you would check the game state to see if the event specified in m_on has occurred.
        // If it has, you would then apply the effect specified in m_effect.
        // This is a placeholder implementation. You would need to implement the logic to check for the event and apply the effect based on your game's architecture.
    }

    void TriggeredAbility::from_json(const nlohmann::json &j, IAbility &ability)
    {
        // This is a placeholder implementation. In a real implementation, you would need to deserialize the event type and the triggered effect.
        // For example, you might have a mapping of event types to their corresponding classes, and similarly for triggered effects.
        // You would then use this mapping to create the appropriate instances based on the JSON data.
    }

    void TriggeredAbility::to_json(nlohmann::json &j, const IAbility &ability)
    {
        const auto &triggeredAbility = dynamic_cast<const TriggeredAbility &>(ability);
        j = nlohmann::json{{"type", "TriggeredAbility"}, {"data", nlohmann::json()}};

        j["data"]["on"] = nlohmann::json();
        triggeredAbility.m_on->to_json(j["data"]["on"], *triggeredAbility.m_on);

        j["data"]["effect"] = nlohmann::json();
        triggeredAbility.m_effect->to_json(j["data"]["effect"], *triggeredAbility.m_effect);
    }
}