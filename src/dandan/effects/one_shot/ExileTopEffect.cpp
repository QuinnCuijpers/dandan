#include "dandan/effects/one_shot/ExileTopEffect.h"
#include "dandan/core/Game.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    ExileTopEffect::ExileTopEffect(int amount, core::PlayerID player,
                                   EffectContext context)
        : IOneShotEffect(std::move(context)), m_amount(amount), m_player(player)
    {
    }

    std::unique_ptr<IOneShotEffect> ExileTopEffect::copy() const
    {
        return std::make_unique<ExileTopEffect>(m_amount, m_player,
                                                getEffectContext());
    }

    std::unique_ptr<IOneShotEffect> ExileTopEffectDefinition::bind(
        [[maybe_unused]] const core::ExecutionContext exec_ctx,
        EffectContext context) const
    {
        return std::make_unique<ExileTopEffect>(m_amount, context.player_id,
                                                context);
    }

    std::unique_ptr<IOneShotEffectDefinition> ExileTopEffectDefinition::clone()
        const
    {
        return std::make_unique<ExileTopEffectDefinition>(m_amount);
    }

    ExileTopEffectDefinition::ExileTopEffectDefinition(int amount)
        : m_amount(amount)
    {
    }

    int ExileTopEffectDefinition::getAmount() const
    {
        return m_amount;
    }

    std::unique_ptr<events::IEvent> ExileTopEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        for (int i = 0; i < m_amount; ++i)
        {
            if (game.library().getCards().empty())
            {
                break;
            }
            auto card_id{game.library().getCards().front()};
            auto *card{card_registry.get(card_id)};
            game.moveCardFromZone(game.activePlayer(), *card);
            game.exile().addCard(*card);
        }
        return nullptr;
    }
} // namespace dandan::effects
