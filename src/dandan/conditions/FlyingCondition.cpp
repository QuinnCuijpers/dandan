#include "dandan/conditions/FlyingCondition.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/KeyWords.h"

namespace
{
    bool isFlyingAbility(const dandan::abilities::IAbility &ability)
    {
        const auto *static_ability =
            dynamic_cast<const dandan::abilities::StaticAbility *>(&ability);
        if ((static_ability == nullptr) ||
            static_ability->getType() !=
                dandan::abilities::StaticAbility::Type::Prevention)
        {
            return false;
        }
        const auto *effect =
            dynamic_cast<const dandan::effects::BlockPreventionEffect *>(
                static_ability->getEffect());
        if (effect == nullptr)
        {
            return false;
        }
        return dynamic_cast<const dandan::conditions::FlyingCondition *>(
                   effect->getCondition()) != nullptr;
    }
} // namespace

namespace dandan::conditions
{
    bool FlyingCondition::isSatisfied(
        const core::Game &game,
        std::optional<effects::EffectContext> context) const
    {
        const auto *card{game.getCardByID(context->card_id.value())};
        const auto &current_abilities{card->getCurrentAbilities()};
        return std::any_of(current_abilities.begin(), current_abilities.end(),
                           [](const abilities::BoundAbility &ability)
                           { return isFlyingAbility(ability.definition()); });
    }
} // namespace dandan::conditions