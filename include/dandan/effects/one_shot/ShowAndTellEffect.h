#ifndef DANDAN_SHOWANDTELLEFFECT_H
#define DANDAN_SHOWANDTELLEFFECT_H

#include "dandan/core/CardData.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <utility>
namespace dandan::effects
{
    class ShowAndTellEffect : public IOneShotEffect
    {

    public:
        ShowAndTellEffect(core::PlayerID player_id, EffectContext context)
            : IOneShotEffect(std::move(context)), m_player(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ShowAndTellEffect>(m_player,
                                                       getEffectContext());
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        const std::array<core::CardData::Type, 4> m_types{
            core::CardData::Type::Artifact, core::CardData::Type::Creature,
            core::CardData::Type::Enchantment, core::CardData::Type::Land};
        core::PlayerID m_player;
    };

    class ShowAndTellEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        ShowAndTellEffectDefinition(core::TargetRequirement target_requirement)
            : m_target_requirements(std::move(target_requirement))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            EffectContext context) const override
        {
            auto player_id{context.player_id.value()};
            return std::make_unique<ShowAndTellEffect>(player_id, context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ShowAndTellEffectDefinition>(
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