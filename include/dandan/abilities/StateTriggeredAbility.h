
#ifndef DANDAN_STATETRIGGEREDABILITY_H
#define DANDAN_STATETRIGGEREDABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
namespace dandan::abilities
{
    /** @brief A triggered ability that activates when a specific condition
     * becomes satisfied.
     * @class StateTriggeredAbility
     *
     * @implements IAbility
     */
    class StateTriggeredAbility final : public IAbility
    {
    public:
        /** Constructor
         * @param condition The condition for the ability
         * @param effect The effect of the ability
         */
        StateTriggeredAbility(
            std::unique_ptr<conditions::ICondition> condition,
            std::unique_ptr<effects::IOneShotEffectDefinition> effect);

        /** Create an effect instance for this ability.
         * @param game The game instance.
         * @param context The ability context.
         * @return The created effect instance.
         */
        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] AbilityContext context) const override;

        /** Get the condition for the ability as a const pointer
         * @return The condition for the ability
         */
        [[nodiscard]] const conditions::ICondition *condition() const;

        /** Get the condition for the ability as a mutable pointer
         * @return The condition for the ability
         */
        [[nodiscard]] conditions::ICondition *condition();

        /** Get the effect of the ability
         * @return The effect of the ability
         */
        [[nodiscard]] const effects::IOneShotEffectDefinition *getEffect()
            const;

    private:
        std::unique_ptr<conditions::ICondition> m_condition;
        std::unique_ptr<effects::IOneShotEffectDefinition> m_effect;
    };
} // namespace dandan::abilities

#endif
