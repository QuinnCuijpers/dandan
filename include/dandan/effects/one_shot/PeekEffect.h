#ifndef DANDAN_PEEK_EFFECT_H
#define DANDAN_PEEK_EFFECT_H

#include "IOneShotEffect.h"

namespace dandan::effects
{

    struct PeekEffect final : public IOneShotEffect
    {
        int m_peek_amount{3};

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<PeekEffect>(m_peek_amount);
        }

        PeekEffect() = default;

        explicit PeekEffect(int peek_amount) : m_peek_amount(peek_amount)
        {
        }
        // TODO: should ask for rearranging similar to scry
        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;
    };
} // namespace dandan::effects

#endif