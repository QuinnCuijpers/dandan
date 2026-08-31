#ifndef DANDAN_LOSE_GAME_EFFECT_H
#define DANDAN_LOSE_GAME_EFFECT_H

#include "dandan/core/GameState.h"
#include "dandan/core/PlayerID.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <utility>

namespace dandan::effects
{
    /** @brief Represents an effect that causes a player to lose the game.
     * @class LoseGameEffect
     *
     * @implements IOneShotEffect
     */
    class LoseGameEffect : public IOneShotEffect
    {
    public:
        /** @brief Constructs a new lose game effect.
         * @param player The player to cause to lose the game.
         */
        explicit LoseGameEffect(const core::PlayerID &player,
                                EffectContext context)
            : IOneShotEffect(std::move(context)), m_player(player)
        {
        }

        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override
        {
            const auto &game{exec_ctx.state.get()};
            const auto &player = game.getPlayer(m_player);

            std::cout << player.getName() << " has lost the game!" << '\n';
            game.quit(player);
            return nullptr;
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<LoseGameEffect>(m_player,
                                                    getEffectContext());
        }

    private:
        core::PlayerID m_player;
    };
} // namespace dandan::effects

#endif
