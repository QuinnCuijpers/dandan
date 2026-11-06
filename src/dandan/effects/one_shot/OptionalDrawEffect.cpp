#include "dandan/effects/one_shot/OptionalDrawEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/effects/one_shot/DrawEffect.h"
#include <memory>
#include <string>
#include <utility>

namespace dandan::effects
{
    OptionalDrawEffect::OptionalDrawEffect(int amount, bool each_player,
                                           EffectContext context)
        : IOneShotEffect(std::move(context)), m_amount(amount),
          m_each_player(each_player)
    {
    }

    std::unique_ptr<IOneShotEffect> OptionalDrawEffect::copy() const
    {
        return std::make_unique<OptionalDrawEffect>(m_amount, m_each_player,
                                                    getEffectContext());
    }

    std::unique_ptr<IOneShotEffect> OptionalDrawEffectDefinition::bind(
        [[maybe_unused]] const core::ExecutionContext exec_ctx,
        [[maybe_unused]] EffectContext context) const
    {
        return std::make_unique<OptionalDrawEffect>(m_amount, m_each_player,
                                                    context);
    }

    std::unique_ptr<IOneShotEffectDefinition> OptionalDrawEffectDefinition::
        clone() const
    {
        return std::make_unique<OptionalDrawEffectDefinition>(m_amount,
                                                              m_each_player);
    }

    OptionalDrawEffectDefinition::OptionalDrawEffectDefinition(int amount,
                                                               bool each_player)
        : m_amount(amount), m_each_player(each_player)
    {
    }

    int OptionalDrawEffectDefinition::getAmount() const
    {
        return m_amount;
    }

    bool OptionalDrawEffectDefinition::isEachPlayer() const
    {
        return m_each_player;
    }

    std::unique_ptr<events::IEvent> OptionalDrawEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        if (m_each_player)
        {
            auto starting_player_id{game.activePlayer().getID()};
            auto current_player_id{starting_player_id};

            while (true)
            {
                auto &player{game.getPlayer(current_player_id)};
                std::cout << player.getName()
                          << ", how many cards do you want to draw (0-"
                          << m_amount << ")?\n";

                std::string input;
                std::getline(istream, input);
                int draw_amount{std::stoi(input)};

                auto def{dandan::effects::DrawEffectDefinition(draw_amount)};
                auto context{EffectContext{player.getID()}};
                auto effect{def.bind(exec_ctx, context)};
                static_cast<void>(effect->apply(exec_ctx));

                current_player_id = game.getNextPlayerID(current_player_id);
                if (current_player_id == starting_player_id)
                {
                    break;
                }
            }
        }
        else
        {
            game.activePlayer().drawCard(exec_ctx);
        }
        return nullptr;
    }
} // namespace dandan::effects
