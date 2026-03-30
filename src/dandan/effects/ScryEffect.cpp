#include "dandan/effects/ScryEffect.h"
#include "dandan/abilities/TriggeredAbility.h"
#include <nlohmann/json.hpp>

namespace dandan::effects
{

    void ScryEffect::apply()
    {
        // Implement the logic for applying the scry effect here.
        // This is a placeholder implementation. In a real implementation, you would need to interact with the game state to perform the scry action.
    }

    void ScryEffect::from_json(const nlohmann::json &j, ITriggeredEffect &effect)
    {
    }

    void ScryEffect::to_json(nlohmann::json &j, const ITriggeredEffect &effect)
    {
        const auto &scryEffect = dynamic_cast<const ScryEffect &>(effect);
        j = nlohmann::json{{"type", "ScryEffect"}, {"data", nlohmann::json()}};
        j["data"]["scry_amount"] = scryEffect.m_scry_amount;
    }

}