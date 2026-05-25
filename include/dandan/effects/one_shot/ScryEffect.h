#ifndef DANDAN_SCRY_EFFECT_H
#define DANDAN_SCRY_EFFECT_H

#include "IOneShotEffect.h"

namespace dandan::effects
{

    struct ScryEffect final : public IOneShotEffect
    {
        int m_scry_amount{1};

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            return std::make_unique<ScryEffect>(m_scry_amount);
        }

        ScryEffect() = default;

        explicit ScryEffect(int scry_amount) : m_scry_amount(scry_amount)
        {
        }

        std::unique_ptr<events::IEvent> apply(core::Game &game) const override;
    };
} // namespace dandan::effects

#endif