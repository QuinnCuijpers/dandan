#ifndef DANDAN_SPINTOTOPEFFECT_H
#define DANDAN_SPINTOTOPEFFECT_H

#include <memory>
#include <utility>
#include <variant>

#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class SpinToTopEffect : public IOneShotEffect
    {

    public:
        SpinToTopEffect(core::Target target, EffectContext context);

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        core::Target m_target;
    };

    class SpinToTopEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        explicit SpinToTopEffectDefinition(core::TargetRequirement target_req)
            : m_target_requirements(std::move(target_req))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::Game &game, EffectContext context) const override
        {
            const auto *card{game.getCardByID(context.card_id.value())};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            return std::make_unique<SpinToTopEffect>(choice, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<SpinToTopEffectDefinition>(
                m_target_requirements);
        }

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override
        {
            return &m_target_requirements;
        }

    private:
        core::TargetRequirement m_target_requirements;
    };
} // namespace dandan::effects

#endif
