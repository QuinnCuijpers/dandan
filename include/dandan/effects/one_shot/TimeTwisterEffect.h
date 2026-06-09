#ifndef DANDAN_TIMETWISTEREFFECT_H
#define DANDAN_TIMETWISTEREFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    class TimeTwisterEffect : public IOneShotEffect,
                              public IOneShotEffectDefinition
    {
    public:
        TimeTwisterEffect() = default;

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<TimeTwisterEffect>();
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<TimeTwisterEffect>();
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] EffectContext context) const override
        {
            return copy();
        }
    };
} // namespace dandan::effects

#endif