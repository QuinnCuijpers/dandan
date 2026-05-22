#include "dandan/abilities/TriggeredAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{

    std::unique_ptr<effects::IOneShotEffect> TriggeredAbility::createEffect(
        core::Game &game, [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving triggered ability\n";
        m_effect->apply(game);
        return nullptr;
    }

} // namespace dandan::abilities