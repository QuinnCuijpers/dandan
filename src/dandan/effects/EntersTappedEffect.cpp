#include "dandan/effects/EntersTappedEffect.h"
#include "dandan/events/IEvent.h"
#include "dandan/events/EntersBattleFieldEvent.h"
#include <nlohmann/json.hpp>

namespace dandan::effects
{

    std::unique_ptr<events::IEvent> EntersTappedEffect::replace(events::IEvent &event)
    {

        if (auto *enters_battlefield_event = dynamic_cast<events::EntersBattlefieldEvent *>(&event))
        {
            enters_battlefield_event->setTapped(true);
            return std::make_unique<events::EntersBattlefieldEvent>(*enters_battlefield_event);
        }
        return nullptr;
    }

    void EntersTappedEffect::from_json(const nlohmann::json &j, IReplacementEffect &effect)
    {
        // This is a placeholder implementation. In a real implementation, you would need to deserialize any relevant data for the effect.
        // For example, if the effect had parameters (like how long it lasts, or specific conditions), you would extract those from the JSON and set them on the effect instance.
    }

    void EntersTappedEffect::to_json(nlohmann::json &j, const IReplacementEffect &effect)
    {
        j = nlohmann::json{{"type", "EntersTappedEffect"}, {"data", nlohmann::json()}};
    }
}