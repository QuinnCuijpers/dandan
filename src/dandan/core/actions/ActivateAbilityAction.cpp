
#include "dandan/core/actions/ActivateAbilityAction.h"
#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/BasicLandAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/abilities/WithDamage.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>

namespace dandan::core
{

    ActivateAbilityAction::ActivateAbilityAction(
        const abilities::IAbility *ability, abilities::AbilityContext context)
        : m_ability(ability), m_context(std::move(context))
    {
    }
    std::unique_ptr<effects::IOneShotEffect> ActivateAbilityAction::
        createEffect(core::ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        if (const auto *mana_ability =
                dynamic_cast<const abilities::ManaAbility *>(m_ability))
        {
            auto effect = mana_ability->createEffect(exec_ctx, m_context);
            if (effect)
            {
                return effect;
            }
        }
        if (const auto *BasicLandAbility =
                dynamic_cast<const abilities::BasicLandAbility *>(m_ability))
        {
            auto effect = BasicLandAbility->createEffect(exec_ctx, m_context);
            if (effect)
            {
                return effect;
            }
        }
        if (const auto *activated_ability =
                dynamic_cast<const abilities::ActivatedAbility *>(m_ability))
        {
            auto *card{card_registry.get(m_context.source_card_id)};
            activated_ability->getCost()->pay(exec_ctx, m_context);
            game.stack().push(
                abilities::BoundAbility{*activated_ability, card,
                                        m_context.chosen_mode_index,
                                        m_context.text_replacements});
            return nullptr;
        }
        if (const auto *with_damage =
                dynamic_cast<const abilities::WithDamage *>(m_ability))
        {
            auto *card{card_registry.get(m_context.source_card_id)};

            // Mana abilities (possibly wrapped in a decorator such as
            // WithDamage) resolve immediately and never use the stack, so the
            // mana is available for the very next action.
            const auto *inner{with_damage->getInnerAbility()};
            if (dynamic_cast<const abilities::ManaAbility *>(inner) != nullptr ||
                dynamic_cast<const abilities::BasicLandAbility *>(inner) !=
                    nullptr)
            {
                auto effect{with_damage->createEffect(exec_ctx, m_context)};
                if (effect)
                {
                    return effect;
                }
            }

            game.stack().push(
                abilities::BoundAbility{*with_damage, card,
                                        m_context.chosen_mode_index,
                                        m_context.text_replacements});
            return nullptr;
        }
        throw std::runtime_error(
            "Unknown ability type for activated ability action");
    }
} // namespace dandan::core
