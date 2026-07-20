
#ifndef DANDAN_BOUNCEEffect_H
#define DANDAN_BOUNCEEffect_H

#include <stdexcept>
#include <utility>

#include "dandan/core/Game.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
namespace dandan::effects
{
    class BounceEffect : public IOneShotEffect
    {

    public:
        explicit BounceEffect(core::Target target, EffectContext context)
            : IOneShotEffect(std::move(context)), m_target(std::move(target))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<BounceEffect>(m_target, getEffectContext());
        }

        [[nodiscard]] std::string display() const override
        {
            return "Return target spell or creature to its owner's hand.";
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        core::Target m_target;
    };

    class BounceEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        explicit BounceEffectDefinition(
            core::TargetRequirement target_requirements)
            : m_target_requirements(std::move(target_requirements))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            if (!context.card_id.has_value())
            {
                throw std::runtime_error(
                    "tried binding a Bounce Effect without a source card");
            }

            auto source{context.card_id.value()};
            const auto *card{game.getCardByID(source)};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            return std::make_unique<BounceEffect>(choice, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<BounceEffectDefinition>(
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