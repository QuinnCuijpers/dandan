#include "dandan/abilities/WithDamage.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{

    std::unique_ptr<effects::IOneShotEffect> WithDamage::createEffect(
        core::Game &game, AbilityContext context) const
    {
        std::cout << "Resolving WithDamage decorator\n";
        std::cout << "Dealing " << m_damage << " damage\n";
        return m_ability->createEffect(game, context);
    }
} // namespace dandan::abilities