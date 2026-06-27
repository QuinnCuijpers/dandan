#ifndef DANDAN_CHANGECHARACTERISTICS_H
#define DANDAN_CHANGECHARACTERISTICS_H

#include "dandan/core/CardCharacteristics.h"
#include "dandan/core/Game.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace dandan::effects
{
    class ChangeCharacteristicsEffect : public IOneShotEffect
    {

    public:
        ChangeCharacteristicsEffect(core::Target target, EffectContext context)
            : IOneShotEffect(std::move(context)), m_target(std::move(target))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ChangeCharacteristicsEffect>(
                m_target, getEffectContext());
        }

        std::unique_ptr<events::IEvent> apply_impl(
            [[maybe_unused]] core::Game &game) const override
        {
            throw std::runtime_error(
                "Unimplemented apply impl for change characteristics");
        }

    private:
        core::Target m_target;
    };

    class ChangeCharacteristicsEffectDefinition
        : public IOneShotEffectDefinition
    {

    public:
        explicit ChangeCharacteristicsEffectDefinition(
            core::TargetRequirement target_reqs,
            core::CardCharacteristics characteristics)
            : m_target_requirements(std::move(target_reqs)),
              m_card_characteristics(std::move(characteristics))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::Game &game, EffectContext context) const override
        {
            const auto *card{game.getCardByID(context.card_id.value())};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            return std::make_unique<ChangeCharacteristicsEffect>(choice,
                                                                 context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ChangeCharacteristicsEffectDefinition>(
                m_target_requirements, m_card_characteristics);
        }

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override
        {
            return &m_target_requirements;
        }

        [[nodiscard]] core::CardCharacteristics getCharacteristics() const
        {
            return m_card_characteristics;
        }

    private:
        core::TargetRequirement m_target_requirements;
        core::CardCharacteristics m_card_characteristics;
    };
} // namespace dandan::effects

#endif