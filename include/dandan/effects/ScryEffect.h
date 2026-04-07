#ifndef DANDAN_SCRY_EFFECT_H
#define DANDAN_SCRY_EFFECT_H

#include "IEffect.h"

namespace dandan::effects
{

    struct ScryEffect : public IEffect
    {
        int m_scry_amount{1};

        ScryEffect(int scry_amount) : m_scry_amount(scry_amount)
        {
        }

        void apply() override;
    };
} // namespace dandan::effects

#endif