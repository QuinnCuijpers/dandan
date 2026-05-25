
#include "dandan/core/actions/ActivateAbilityAction.h"
#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/ManaAbility.h"
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
            return mana_ability->createEffect(game, m_context);
        }
        if (const auto *activated_ability =
                dynamic_cast<const abilities::ActivatedAbility *>(m_ability))
        {
            return activated_ability->createEffect(game, m_context);
        }
        throw std::runtime_error(
            "Unknown ability type for activated ability action");
    }
} // namespace dandan::core