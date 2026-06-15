
#include "dandan/core/actions/ActivateAbilityAction.h"
#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/BasicLandAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/abilities/WithDamage.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::core
{
    std::unique_ptr<effects::IOneShotEffect> ActivateAbilityAction::
        createEffect(core::Game &game)
    {
        if (const auto *mana_ability =
                dynamic_cast<const abilities::ManaAbility *>(m_ability))
        {
            auto effect = mana_ability->createEffect(game, m_context);
            if (effect)
            {
                return effect;
            }
        }
        if (const auto *BasicLandAbility =
                dynamic_cast<const abilities::BasicLandAbility *>(m_ability))
        {
            auto effect = BasicLandAbility->createEffect(game, m_context);
            if (effect)
            {
                return effect;
            }
        }
        if (const auto *activated_ability =
                dynamic_cast<const abilities::ActivatedAbility *>(m_ability))
        {
            auto *card{game.getCardByID(m_context.source_card_id)};
            activated_ability->getCost()->pay(game, m_context);
            game.stack().push(
                abilities::BoundAbility{*activated_ability, card});
            return nullptr;
        }
        if (const auto *with_damage =
                dynamic_cast<const abilities::WithDamage *>(m_ability))
        {
            auto *card{game.getCardByID(m_context.source_card_id)};
            game.stack().push(abilities::BoundAbility{*with_damage, card});
            return nullptr;
        }
        throw std::runtime_error(
            "Unknown ability type for activated ability action");
    }
} // namespace dandan::core