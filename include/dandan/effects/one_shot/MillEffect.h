#ifndef DANDAN_MILL_EFFECT_H
#define DANDAN_MILL_EFFECT_H

#include "dandan/core/Game.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>

namespace dandan::effects
{
    class MillEffect : public IOneShotEffect
    {
    public:
        MillEffect(int amount, core::PlayerID player_id)
            : m_amount(amount), m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<MillEffect>(m_amount, m_player_id);
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        int m_amount;
        core::PlayerID m_player_id;
    };

    class MillEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        MillEffectDefinition(int amount,
                             core::TargetRequirement target_requirement)
            : m_amount(amount),
              m_target_requirement(std::move(target_requirement))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            auto *card{game.getCardByID(context.card()->getID())};
            auto choices{card->getTargetChoices(*this)};
            auto choice{choices.at(0)};
            auto player_choice{std::get<core::PlayerID>(choice)};
            return std::make_unique<MillEffect>(m_amount, player_choice);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<MillEffectDefinition>(m_amount,
                                                          m_target_requirement);
        }

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

        [[nodiscard]] const core::TargetRequirement *getTargetRequirement()
            const override
        {
            return &m_target_requirement;
        }

    private:
        int m_amount;
        core::TargetRequirement m_target_requirement;
    };
} // namespace dandan::effects

#endif