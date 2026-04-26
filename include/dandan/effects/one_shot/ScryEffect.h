#ifndef DANDAN_SCRY_EFFECT_H
#define DANDAN_SCRY_EFFECT_H

#include "IOneShotEffect.h"

namespace dandan::effects
{

    struct ScryEffect final : public IOneShotEffect
    {
        int m_scry_amount{1};

        ScryEffect() = default;

        explicit ScryEffect(int scry_amount) : m_scry_amount(scry_amount)
        {
        }

        void apply() override;
    };
} // namespace dandan::effects

#endif