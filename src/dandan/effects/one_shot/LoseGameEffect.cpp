#include "dandan/effects/one_shot/LoseGameEffect.h"
#include <iostream>
#include <memory>
#include <utility>

namespace dandan::effects
{
    LoseGameEffect::LoseGameEffect(const core::PlayerID &player,
                                   EffectContext context)
        : IOneShotEffect(std::move(context)), m_player(player)
    {
    }

    std::unique_ptr<IOneShotEffect> LoseGameEffect::copy() const
    {
        return std::make_unique<LoseGameEffect>(m_player, getEffectContext());
    }

    std::unique_ptr<events::IEvent> LoseGameEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        const auto &game{exec_ctx.state.get()};
        const auto &player = game.getPlayer(m_player);

        std::cout << player.getName() << " has lost the game!" << '\n';
        game.quit(player);
        return nullptr;
    }
} // namespace dandan::effects
