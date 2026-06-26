#ifndef DANDAN_CHANGE_LAND_TYPE_EFFECT_H
#define DANDAN_CHANGE_LAND_TYPE_EFFECT_H

#include "dandan/core/SubType.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>
namespace dandan::effects
{
    class ChangeLandTypeEffect : public IOneShotEffect
    {
    public:
        explicit ChangeLandTypeEffect(EffectContext context)
            : IOneShotEffect(std::move(context))
        {
        }

        ChangeLandTypeEffect(core::SubType basic_land_1,
                             core::SubType basic_land_2, EffectContext context)
            : IOneShotEffect(std::move(context)), m_basic_land_1(basic_land_1),
              m_basic_land_2(basic_land_2) {};

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            if (m_basic_land_1.has_value() && m_basic_land_2.has_value())
            {
                return std::make_unique<ChangeLandTypeEffect>(
                    m_basic_land_1.value(), m_basic_land_2.value(),
                    getEffectContext());
            }

            return std::make_unique<ChangeLandTypeEffect>(getEffectContext());
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        std::optional<core::SubType> m_basic_land_1;
        std::optional<core::SubType> m_basic_land_2;
    };

    class ChangeLandTypeEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<ChangeLandTypeEffect>(context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ChangeLandTypeEffectDefinition>();
        }

        [[nodiscard]] std::string display() const override
        {
            return "Choose a land type and a basic land type. Each land of the "
                   "first chosen type becomes the second chosen type until end "
                   "of turn.";
        }
    };
} // namespace dandan::effects

#endif