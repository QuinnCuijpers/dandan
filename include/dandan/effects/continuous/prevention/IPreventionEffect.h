#ifndef DANDAN_IPREVENTION_EFFECT_H
#define DANDAN_IPREVENTION_EFFECT_H

#include "../IContinuousEffect.h"
#include "dandan/core/actions/IAction.h"

namespace dandan::core
{
    class Game;
}

namespace dandan::conditions
{
    class ICondition;
}

namespace dandan::effects
{
    /** The abstract class for prevention effects. Prevention effects prevent
     * certain actions from being performed. They listen to actions as they are
     * being performed and can prevent them from being executed by returning
     * true from the `prevents` method.
     * @class IPreventionEffect
     * @implements IContinuousEffect
     */
    class IPreventionEffect : public IContinuousEffect
    {
    public:
        /** Base constructor for a new prevention effect with a given
         * condition.
         * @param condition The condition under which to prevent the action.
         */
        explicit IPreventionEffect(
            std::unique_ptr<conditions::ICondition> condition)
            : m_condition(std::move(condition))
        {
        }

        /** Determines if this prevention effect prevents the given action.
         * @param action The action to check.
         * @param game The game state.
         * @return True if the prevention effect prevents the action, false
         * otherwise.
         */
        [[nodiscard]] virtual bool prevents(const core::IAction &action,
                                            const core::Game &game) = 0;

        /** Gets the condition associated with this prevention effect.
         * @return A pointer to the condition associated with this prevention
         * effect.
         */
        [[nodiscard]] const conditions::ICondition *getCondition() const
        {
            return m_condition.get();
        }

    private:
        std::unique_ptr<conditions::ICondition> m_condition;
    };

} // namespace dandan::effects

#endif // DANDAN_IPREVENTION_EFFECT_H