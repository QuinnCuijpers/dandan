#include "dandan/effects/one_shot/PutCardOnTopEffect.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <string>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> PutCardOnTopEffect::apply_impl(
        core::Game &game) const
    {
        std::cout << "Applying put card on top effect\n";

        if (m_amount == 1)
        {
            auto hand_size = game.activePlayer().hand().getCards().size();
            if (hand_size == 0)
            {
                std::cout << "No cards in hand to put on top\n";
                return nullptr;
            }
            std::cout << "Which card index do you want to put on top? (0-"
                      << hand_size - 1 << ")\n";
            std::string input;
            getline(game.istream(), input);
            auto index = std::stoi(input);

            // moves card out of hand
            auto card{game.activePlayer().hand().getCard(index)};
            game.library().getCards().push_front(card);

            return nullptr;
        }
        // Break down the effect into multiple single card draws to trigger
        // any relevant state triggers
        for (int i = 0; i < m_amount; ++i)
        {
            auto draw_effect{std::make_unique<PutCardOnTopEffect>(1)};
            draw_effect->apply(game);
        }

        return nullptr;
    }

    std::unique_ptr<IOneShotEffect> PutCardOnTopEffect::clone() const
    {
        return std::make_unique<PutCardOnTopEffect>(m_amount);
    }

} // namespace dandan::effects