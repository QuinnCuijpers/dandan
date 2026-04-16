#ifndef DANDAN_DRAWEFFECT_H
#define DANDAN_DRAWEFFECT_H

#include "IEffect.h"

namespace dandan::effects
{
    struct DrawEffect final : public IEffect
    {
    public:
        int m_amount{1};

        DrawEffect() = default;
        explicit DrawEffect(int amount) : m_amount(amount)
        {
        }

        void apply() override;
    };

} // namespace dandan::effects

#endif