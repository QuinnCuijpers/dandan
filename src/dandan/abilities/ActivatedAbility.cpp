#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{
    std::unique_ptr<effects::IOneShotEffect> ActivatedAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->evaluate();
        return nullptr;
    }

} // namespace dandan::abilities