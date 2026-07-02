#include "dandan/conditions/FlyingCondition.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/Keyword.h"
namespace
{

} // namespace

namespace dandan::conditions
{
    bool FlyingCondition::isSatisfied(
        const core::Game &game,
        std::optional<effects::EffectContext> context) const
    {
        const auto *card{game.getCardByID(context->card_id.value())};
        const auto &current_abilities{card->getCurrentAbilities()};
        return std::any_of(
            current_abilities.begin(), current_abilities.end(),
            [](const abilities::BoundAbility &ability)
            { return core::isFlyingAbility(ability.definition()); });
    }
} // namespace dandan::conditions