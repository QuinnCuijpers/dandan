#ifndef DANDAN_MINDBENDEFFECT_H
#define DANDAN_MINDBENDEFFECT_H

#include <utility>

#include "dandan/core/Game.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
namespace dandan::effects
{
    class MindBendEffect : public IOneShotEffect
    {

    public:
        MindBendEffect(core::Target target) : m_target(std::move(target))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<MindBendEffect>(m_target);
        }

        [[nodiscard]] std::string display() const override
        {
            return "Change the text of target permanent by replacing all "
                   "instances of one color word with another or one basic land "
                   "type with another.";
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        core::Target m_target;
    };

    class MindBendEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        MindBendEffectDefinition(core::TargetRequirement target_requirements)
            : m_target_requirements(std::move(target_requirements))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            const auto *card{game.getCardByID(context.card()->getID())};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            return std::make_unique<MindBendEffect>(choice);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<MindBendEffectDefinition>(
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