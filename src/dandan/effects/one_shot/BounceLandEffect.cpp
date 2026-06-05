#include "dandan/effects/one_shot/BounceLandEffect.h"
#include "dandan/core/Game.h"
#include <iostream>
#include <string>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> BounceLandEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        std::cout << "Applying BounceLandEffect\n";
        std::cout << "what land index to bounce? ";
        std::string input;
        std::getline(game.istream(), input);
        int land_index{std::stoi(input)};
        std::cout << "Bouncing land at index " << land_index << "\n";
        auto land{game.activePlayer().battlefield().getLand(land_index)};
        auto *card{game.getCardByID(land.getID())};
        game.eventManager().unsubscribe(*card);
        game.activePlayer().hand().addCard(*card);
        return nullptr;
    }
} // namespace dandan::effects