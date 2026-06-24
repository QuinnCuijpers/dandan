#ifndef DANDAN_TIMETWISTEREFFECT_H
#define DANDAN_TIMETWISTEREFFECT_H

#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    class TimeTwisterEffect : public IOneShotEffect
    {
    public:
        TimeTwisterEffect(EffectContext context)
            : IOneShotEffect(std::move(context))
        {
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<TimeTwisterEffect>(getEffectContext());
        }
    };

    class TimeTwisterEffectDefinition : public IOneShotEffectDefinition
    {
        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<TimeTwisterEffectDefinition>();
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<TimeTwisterEffect>(context);
        }
    };
} // namespace dandan::effects

#endif