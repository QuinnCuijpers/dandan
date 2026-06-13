#ifndef DANDAN_CHANGE_LAND_TYPE_EFFECT_H
#define DANDAN_CHANGE_LAND_TYPE_EFFECT_H

#include "dandan/core/CardData.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <optional>
namespace dandan::effects
{
    class ChangeLandTypeEffect : public IOneShotEffect
    {
    public:
        ChangeLandTypeEffect() = default;

        ChangeLandTypeEffect(core::SubType basic_land_1,
                             core::SubType basic_land_2)
            : m_basic_land_1(basic_land_1), m_basic_land_2(basic_land_2) {};

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ChangeLandTypeEffect>();
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
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<ChangeLandTypeEffect>();
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