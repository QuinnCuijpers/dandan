#include "dandan/conditions/PlayedLandCondition.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/Game.h"
#include "dandan/core/TextReplacement.h"
#include <optional>
#include <vector>

namespace dandan::conditions
{
    bool PlayedLandCondition::isSatisfied(
        const core::Game &game,
        [[maybe_unused]] std::optional<abilities::AbilityContext> context) const
    {
        return game.activePlayer().playedLandThisTurn();
    }
} // namespace dandan::conditions