#include "dandan/abilities/Events.h"
#include <nlohmann/json.hpp>

namespace dandan::abilities
{

    void EntersBattlefieldEvent::to_json(nlohmann::json &j, const IEvent &event) const
    {
        const auto &entersBattlefieldEvent = dynamic_cast<const EntersBattlefieldEvent &>(event);
        j = nlohmann::json{{"type", "EntersBattlefieldEvent"}, {"data", nlohmann::json()}};
        if (entersBattlefieldEvent.m_tapped.has_value())
        {
            j["data"]["tapped"] = entersBattlefieldEvent.m_tapped.value();
        }
    }
}