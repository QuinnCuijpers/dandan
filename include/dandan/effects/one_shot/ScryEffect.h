#ifndef DANDAN_SCRY_EFFECT_H
#define DANDAN_SCRY_EFFECT_H

#include <utility>

#include "IOneShotEffect.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    /** @brief Reprents the effect of scrying
     * @struct ScryEffect
     *
     * @implements IOneShotEffect
     */
    class ScryEffect final : public IOneShotEffect
    {
    public:
        /** Constructor
         * @param scry_amount the amount of cards to scry
         * @param player the player who will scry
         */
        explicit ScryEffect(int scry_amount, core::PlayerID player,
                            EffectContext context)
            : IOneShotEffect(std::move(context)), m_scry_amount(scry_amount),
              m_player(player)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<ScryEffect>(m_scry_amount, m_player,
                                                getEffectContext());
        }
        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

        [[nodiscard]] int getScryAmount() const
        {
            return m_scry_amount;
        }

    private:
        int m_scry_amount{1};
        core::PlayerID m_player;
    };

    class ScryEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        ScryEffectDefinition() = default;
        explicit ScryEffectDefinition(int scry_amount)
            : m_scry_amount(scry_amount)
        {
        }
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            EffectContext context) const override
        {
            return std::make_unique<ScryEffect>(
                m_scry_amount, context.player_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<ScryEffectDefinition>(m_scry_amount);
        }

        [[nodiscard]] int getScryAmount() const
        {
            return m_scry_amount;
        }

    private:
        int m_scry_amount{1};
    };
} // namespace dandan::effects

#endif
