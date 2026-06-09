#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{

    std::unique_ptr<effects::IOneShotEffect> EventTriggeredAbility::
        createEffect([[maybe_unused]] core::Game &game,
                     [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving triggered ability\n";
        return m_effect->bind(effects::EffectContext(context.controller_id));
    }

} // namespace dandan::abilities