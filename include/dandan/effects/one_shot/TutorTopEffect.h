#ifndef DANDAN_TUTOR_TOP_EFFECT_H
#define DANDAN_TUTOR_TOP_EFFECT_H

#include "dandan/core/CardData.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    class TutorTopEffect : public IOneShotEffect
    {
    public:
        TutorTopEffect(std::vector<core::CardData::Type> filter_types,
                       core::PlayerID player_id)
            : m_filter_types(std::move(filter_types)), m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<TutorTopEffect>(m_filter_types,
                                                    m_player_id);
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        std::vector<core::CardData::Type> m_filter_types;
        core::PlayerID m_player_id;
    };

    class TutorTopEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        TutorTopEffectDefinition(
            std::vector<dandan::core::CardData::Type> filter_types)
            : m_filter_types(std::move(filter_types))
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            EffectContext context) const override
        {
            return std::make_unique<TutorTopEffect>(m_filter_types,
                                                    context.player().value());
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<TutorTopEffectDefinition>(m_filter_types);
        }

        [[nodiscard]] const std::vector<dandan::core::CardData::Type> &
        getFilterTypes() const
        {
            return m_filter_types;
        }

    private:
        std::vector<dandan::core::CardData::Type> m_filter_types;
    };
} // namespace dandan::effects

#endif