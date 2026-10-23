#include "dandan/effects/one_shot/ScryEffect.h"
#include "dandan/core/GameState.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    ScryEffect::ScryEffect(int scry_amount, core::PlayerID player,
                           EffectContext context)
        : IOneShotEffect(std::move(context)), m_scry_amount(scry_amount),
          m_player(player)
    {
    }

    std::unique_ptr<IOneShotEffect> ScryEffect::copy() const
    {
        return std::make_unique<ScryEffect>(m_scry_amount, m_player,
                                            getEffectContext());
    }

    int ScryEffect::getScryAmount() const
    {
        return m_scry_amount;
    }

    ScryEffectDefinition::ScryEffectDefinition(int scry_amount)
        : m_scry_amount(scry_amount)
    {
    }

    std::unique_ptr<IOneShotEffect> ScryEffectDefinition::bind(
        [[maybe_unused]] const core::ExecutionContext exec_ctx,
        EffectContext context) const
    {
        return std::make_unique<ScryEffect>(m_scry_amount, context.player_id,
                                            context);
    }

    std::unique_ptr<IOneShotEffectDefinition> ScryEffectDefinition::clone()
        const
    {
        return std::make_unique<ScryEffectDefinition>(m_scry_amount);
    }

    int ScryEffectDefinition::getScryAmount() const
    {
        return m_scry_amount;
    }

    std::unique_ptr<events::IEvent> ScryEffect::apply_impl(
        [[maybe_unused]] core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        auto cards = game.library().draw(m_scry_amount);
        std::cout << "Scryed cards: [ ";
        for (const auto &card : cards)
        {
            auto *cardp{card_registry.get(card)};
            std::cout << cardp->getData().name << " ,";
        }
        std::cout << " ]\n";

        while (!cards.empty())
        {
            // choose a card index if cards.size() > 1, otherwise just put the
            // card on top or bottom
            int card_index{-1};
            if (cards.size() > 1)
            {
                std::cout << "Choose a card index to scry (0 to "
                          << cards.size() - 1 << "): ";
                std::string input;
                std::getline(istream, input);
                card_index = std::stoi(input);
                if (card_index < 0 ||
                    card_index >= static_cast<int>(cards.size()))
                {
                    std::cout << "Invalid card index";
                    continue;
                }
            }
            else
            {
                card_index = 0;
            }

            // ask to put on top or bottom
            std::cout << "Put card on top or bottom? (top/bottom) ";
            std::string input;
            std::getline(istream, input);
            if (input == "top")
            {
                game.library().getCards().push_front(cards[card_index]);
                cards.erase(cards.begin() + card_index);
            }
            else if (input == "bottom")
            {
                game.library().getCards().push_back(cards[card_index]);
                cards.erase(cards.begin() + card_index);
            }
            else
            {
                std::cout << "Invalid input, please enter top or bottom\n";
                continue;
            }
        }
        return nullptr;
    }

} // namespace dandan::effects
