#include "dandan/abilities/TriggeredAbility.h"
#include "dandan/core/Game.h"
#include <iostream>

namespace dandan::abilities
{

    void TriggeredAbility::resolve(
        core::Game &game, [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving triggered ability\n";
        m_effect->apply(game);
    }

} // namespace dandan::abilities