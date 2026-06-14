#ifndef DANDAN_PLAY_CARD_PREVENTION_EFFECT_H
#define DANDAN_PLAY_CARD_PREVENTION_EFFECT_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>

namespace dandan::effects
{
    /** @brief A prevention effect that prevents playing cards under a provided
     * condition.
     * @class PlayCardPreventionEffect
     *
     * @implements IPreventionEffect
     */
    class PlayCardPreventionEffect : public IPreventionEffect
    {
    public:
        /** Constructs a new play card prevention effect with the given
         * condition.
         * @param condition The condition under which to prevent playing cards.
         */
        explicit PlayCardPreventionEffect(
            std::unique_ptr<conditions::ICondition> condition)
            : IPreventionEffect(std::move(condition))
        {
        }

        [[nodiscard]] bool prevents(const core::IAction &action,
                                    const core::Game &game,
                                    std::optional<abilities::AbilityContext>
                                        context = std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<IPreventionEffect> clone() const override
        {
            return std::make_unique<PlayCardPreventionEffect>(cloneCondition());
        }
    };
} // namespace dandan::effects

#endif
