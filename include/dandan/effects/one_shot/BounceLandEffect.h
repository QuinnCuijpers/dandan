#ifndef DANDAN_BOUNCELANDEFFECT_H
#define DANDAN_BOUNCELANDEFFECT_H

#include "IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/events/IEvent.h"
#include <memory>

namespace dandan::effects
{
    /** @brief Represents bouncing a land you control back to your hand
     * @class BounceLandEffect
     *
     * @implements IOneShotEffect
     */
    class BounceLandEffect : public IOneShotEffect
    {
    public:
        explicit BounceLandEffect(core::PlayerID player_id)
            : m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<BounceLandEffect>(m_player_id);
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        core::PlayerID m_player_id;
    };

    class BounceLandEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<BounceLandEffectDefinition>();
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<BounceLandEffect>(context.player().value());
        }
    };
} // namespace dandan::effects

#endif // DANDAN_BOUNCELANDEFFECT_H
