#ifndef DANDAN_DRAW_PREVENTION_EFFECT_H
#define DANDAN_DRAW_PREVENTION_EFFECT_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>

namespace dandan::effects
{
    /** @brief A prevention effect that prevents drawing cards under a provided
     * condition.
     * @class DrawPreventionEffect
     *
     * @implements IPreventionEffect
     */
    class DrawPreventionEffect : public IPreventionEffect
    {
    public:
        /** Constructs a new draw prevention effect with the given condition.
         * @param condition The condition under which to prevent drawing cards.
         */
        explicit DrawPreventionEffect(
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
            return std::make_unique<DrawPreventionEffect>(cloneCondition());
        }
    };
} // namespace dandan::effects

#endif
