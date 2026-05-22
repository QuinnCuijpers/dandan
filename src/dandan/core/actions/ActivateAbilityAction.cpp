
#include "dandan/core/actions/ActivateAbilityAction.h"
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
        return nullptr;
    }
} // namespace dandan::core