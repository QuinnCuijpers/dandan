#ifndef DANDAN_PEEK_EFFECT_H
#define DANDAN_PEEK_EFFECT_H

#include "IOneShotEffect.h"

namespace dandan::effects
{

    struct PeekEffect final : public IOneShotEffect
    {
        int m_peek_amount{3};

        PeekEffect() = default;

        explicit PeekEffect(int peek_amount) : m_peek_amount(peek_amount)
        {
        }
        void apply() override;
    };
} // namespace dandan::effects

#endif