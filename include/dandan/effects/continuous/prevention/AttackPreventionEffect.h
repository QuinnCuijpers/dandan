#ifndef DANDAN_ATTACKPREVENTIONEFFECT_H
#define DANDAN_ATTACKPREVENTIONEFFECT_H

#include "IPreventionEffect.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/TextReplacement.h"
#include <memory>
#include <optional>
#include <vector>

namespace dandan::effects
{
    /** @brief A prevention effect that prevents attacking under a provided
     * condition.
     * @class AttackPreventionEffect
     *
     * @implements IPreventionEffect
     */
    class AttackPreventionEffect : public IPreventionEffect
    {
    public:
        /** Constructs a new attack prevention effect with the given condition.
         * @param condition The condition under which to prevent attacking.
         */
        explicit AttackPreventionEffect(
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
            return std::make_unique<AttackPreventionEffect>(cloneCondition());
        }
    };

} // namespace dandan::effects

#endif // DANDAN_ATTACKPREVENTIONEFFECT_H
