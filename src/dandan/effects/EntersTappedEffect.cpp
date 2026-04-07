#include "dandan/effects/EntersTappedEffect.h"
#include "dandan/events/EntersBattleFieldEvent.h"
#include "dandan/events/IEvent.h"
#include <nlohmann/json.hpp>

namespace dandan::effects
{

    std::unique_ptr<events::IEvent> EntersTappedEffect::replace(
        events::IEvent &event)
    {

        if (auto *enters_battlefield_event =
                dynamic_cast<events::EntersBattlefieldEvent *>(&event))
        {
            enters_battlefield_event->setTapped(true);
            return std::make_unique<events::EntersBattlefieldEvent>(
                *enters_battlefield_event);
        }
        return nullptr;
    }

} // namespace dandan::effects