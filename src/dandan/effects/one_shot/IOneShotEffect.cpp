#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/core/Game.h"

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> IOneShotEffect::apply(
        core::Game &game) const
    {
        // TODO: impl as an Event bus
        auto event{apply_impl(game)};
        game.conditionManager().checkConditions(game);
        return event;
    }
} // namespace dandan::effects