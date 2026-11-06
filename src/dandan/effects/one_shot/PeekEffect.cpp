#include "dandan/effects/one_shot/PeekEffect.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/GameState.h"
#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace dandan::effects
{
    PeekEffect::PeekEffect(int peek_amount, core::PlayerID player_id,
                           EffectContext context)
        : IOneShotEffect(std::move(context)), m_peek_amount(peek_amount),
          m_player_id(player_id)
    {
    }

    std::unique_ptr<IOneShotEffect> PeekEffect::copy() const
    {
        return std::make_unique<PeekEffect>(m_peek_amount, m_player_id,
                                            getEffectContext());
    }

    PeekEffectDefinition::PeekEffectDefinition(int peek_amount)
        : m_peek_amount(peek_amount)
    {
    }

    std::unique_ptr<IOneShotEffect> PeekEffectDefinition::bind(
        [[maybe_unused]] core::ExecutionContext exex_ctx,
        EffectContext context) const
    {
        return std::make_unique<PeekEffect>(m_peek_amount, context.player_id,
                                            context);
    }

    std::unique_ptr<IOneShotEffectDefinition> PeekEffectDefinition::clone()
        const
    {
        return std::make_unique<PeekEffectDefinition>(m_peek_amount);
    }

    int PeekEffectDefinition::getPeekAmount() const
    {
        return m_peek_amount;
    }

    void printPeekedCards(const std::vector<core::CardID> &card_ids,
                          core::ExecutionContext exec_ctx)
    {
        const auto &card_registry{exec_ctx.cards.get()};
        std::cout << "Peeked cards: [ ";
        for (size_t i{}; i < card_ids.size(); ++i)
        {
            const auto card_id{card_ids[i]};
            const auto *cardp{card_registry.get(card_id)};
            std::cout << i << ": " << cardp->getData().name << ", ";
        }
        std::cout << " ]\n";
    }

    std::unique_ptr<events::IEvent> PeekEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game = exec_ctx.state.get();
        auto &istream{exec_ctx.input_manager.get().stream()};

        std::cout << "Applying PeekEffect: peeking at the top " << m_peek_amount
                  << " cards of the library\n";
        // moves cards out of deck
        auto cards{game.library().draw(m_peek_amount)};
        printPeekedCards(cards, exec_ctx);

        std::cout << "Which card to put back on top next?\n";
        std::cout << " The last card chosen will be on top\n";

        for (int i{}; i < m_peek_amount; ++i)
        {
            printPeekedCards(cards, exec_ctx);
            std::cout << "Choose card (0 - " << cards.size() - 1 << "): ";
            std::string choice{};
            std::getline(istream, choice);
            int choice_int{std::stoi(choice)};
            if (choice_int < 0 || choice_int >= static_cast<int>(cards.size()))
            {
                std::cout << "Invalid choice. Please try again.\n";
                --i; // Retry the same iteration
            }
            else
            {
                auto chosen_card{cards[choice_int]};
                game.library().getCards().push_front(chosen_card);
                cards.erase(cards.begin() + choice_int);
            }
        }
        return nullptr;
    }

} // namespace dandan::effects
