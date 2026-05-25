#include "dandan/effects/one_shot/DrawEffect.h"

#include "dandan/core/Game.h"
#include <iostream>

namespace dandan::effects
{

    std::unique_ptr<events::IEvent> DrawEffect::apply(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying draw effect\n";
        for (int i = 0; i < m_amount; ++i)
        {
            game.activePlayer().drawCard(game.library(), game);
        }

        return nullptr;
    }

} // namespace dandan::effects