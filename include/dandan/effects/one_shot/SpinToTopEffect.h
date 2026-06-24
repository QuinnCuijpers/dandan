#ifndef DANDAN_SPINTOTOPEFFECT_H
#define DANDAN_SPINTOTOPEFFECT_H

#include <memory>
#include <stdexcept>
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
        SpinToTopEffect(core::Target target, EffectContext context)
            : IOneShotEffect(std::move(context)), m_target(std::move(target))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<SpinToTopEffect>(m_target,
                                                     getEffectContext());
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override
        {
            if (!std::holds_alternative<core::CardID>(m_target))
            {
                throw std::runtime_error(
                    "Spin to top effect target is not a card ID");
            }
            auto permanent{std::get<core::CardID>(m_target)};
            auto *card{game.getCardByID(permanent)};
            game.moveCardFromZone(game.activePlayer(), *card);
            game.library().addCardTop(*card);
            return nullptr;
        }

    private:
        core::Target m_target;
    };

    class SpinToTopEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        SpinToTopEffectDefinition(core::TargetRequirement target_req)
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