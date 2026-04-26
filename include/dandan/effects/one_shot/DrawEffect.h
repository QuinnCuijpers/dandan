#ifndef DANDAN_DRAWEFFECT_H
#define DANDAN_DRAWEFFECT_H

#include "IOneShotEffect.h"

namespace dandan::effects
{
    struct DrawEffect final : public IOneShotEffect
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