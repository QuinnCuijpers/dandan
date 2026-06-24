#ifndef DANDAN_MemoryLapseEFFECT_H
#define DANDAN_MemoryLapseEFFECT_H

#include "dandan/core/Game.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/core/Zone.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>
namespace dandan::effects
{
    class MemoryLapseEffect : public IOneShotEffect
    {

    public:
        explicit MemoryLapseEffect(core::Target target, EffectContext context,
                                   core::Zone target_zone = core::Zone::LIBRARY)
            : IOneShotEffect(std::move(context)), m_target(std::move(target)),
              m_target_zone(target_zone)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<MemoryLapseEffect>(m_target,
                                                       getEffectContext());
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        core::Target m_target;
        core::Zone m_target_zone{core::Zone::LIBRARY};
    };

    class MemoryLapseEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        explicit MemoryLapseEffectDefinition(
            core::TargetRequirement target_requirements)
            : m_target_requirements(std::move(target_requirements))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::Game &game, EffectContext context) const override
        {
            const auto *card{game.getCardByID(context.card_id.value())};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            return std::make_unique<MemoryLapseEffect>(choice, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<MemoryLapseEffectDefinition>(
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