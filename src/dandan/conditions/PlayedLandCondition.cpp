#include "dandan/conditions/PlayedLandCondition.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/Game.h"
#include <optional>

namespace dandan::conditions
{
    bool PlayedLandCondition::isSatisfied(
        const core::Game &game,
        [[maybe_unused]] std::optional<effects::EffectContext> context) const
    {
        return game.activePlayer().playedLandThisTurn();
    }
} // namespace dandan::conditions