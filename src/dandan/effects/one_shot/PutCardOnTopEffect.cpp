#include "dandan/effects/one_shot/PutCardOnTopEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <string>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> PutCardOnTopEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        std::cout << "Applying put card on top effect\n";

        auto &player = game.getPlayer(m_playerID);

        if (m_amount == 1)
        {
            game.printCards(player.hand().getCards(), card_registry);
            auto hand_size = player.hand().getCards().size();
            if (hand_size == 0)
            {
                std::cout << "No cards in hand to put on top\n";
                return nullptr;
            }
            std::cout << "Which card index do you want to put on top? (0-"
                      << hand_size - 1 << ")\n";
            std::string input;
            getline(istream, input);
            auto index = std::stoi(input);

            // moves card out of hand
            auto card{player.hand().getCard(index)};
            game.library().getCards().push_front(card);

            return nullptr;
        }
        // Break down the effect into multiple single card draws to trigger
        // any relevant state triggers
        for (int i = 0; i < m_amount; ++i)
        {
            auto put_effect{std::make_unique<PutCardOnTopEffect>(
                1, m_playerID, getEffectContext())};
            static_cast<void>(put_effect->apply(exec_ctx));
        }

        return nullptr;
    }

    std::unique_ptr<IOneShotEffect> PutCardOnTopEffect::copy() const
    {
        return std::make_unique<PutCardOnTopEffect>(m_amount, m_playerID,
                                                    getEffectContext());
    }

    std::string PutCardOnTopEffect::display() const
    {
        return "Put " + std::to_string(m_amount) +
               " card(s) from your hand on top of your library";
    }

} // namespace dandan::effects
