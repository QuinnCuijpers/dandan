#include "dandan/ReplacementAbility.h"
#include <nlohmann/json.hpp>

std::unique_ptr<IEvent> EntersTappedEffect::replace(IEvent &event)
{
    if (auto *enters_battlefield_event = dynamic_cast<EntersBattlefieldEvent *>(&event))
    {
        enters_battlefield_event->setTapped(true);
        return std::make_unique<EntersBattlefieldEvent>(*enters_battlefield_event);
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