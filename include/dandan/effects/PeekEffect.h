#ifndef DANDAN_PEEK_EFFECT_H
#define DANDAN_PEEK_EFFECT_H

#include "IEffect.h"

namespace dandan::effects
{

    struct PeekEffect : public IEffect
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