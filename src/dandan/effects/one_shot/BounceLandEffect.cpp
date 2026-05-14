#include "dandan/effects/one_shot/BounceLandEffect.h"
#include "dandan/core/Game.h"
#include <iostream>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> BounceLandEffect::apply(
        [[maybe_unused]] core::Game &game)
    {
        std::cout << "Applying BounceLandEffect\n";
        std::cout << "what land index to bounce? ";
        int land_index{};
        game.istream() >> land_index;
        std::cout << "Bouncing land at index " << land_index << "\n";
        auto land{game.activePlayer().battlefield().getPermanent(land_index)};
        game.activePlayer().hand().addCard(land);
        return nullptr;
    }
} // namespace dandan::effects