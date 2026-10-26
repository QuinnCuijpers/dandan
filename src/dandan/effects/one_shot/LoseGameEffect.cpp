#include "dandan/effects/one_shot/LoseGameEffect.h"
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
} // namespace dandan::effects
