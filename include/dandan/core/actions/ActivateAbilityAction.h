#ifndef DANDAN_ACTIVATEABILITYACTION_H
#define DANDAN_ACTIVATEABILITYACTION_H

#include "dandan/abilities/IAbility.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"

namespace dandan::core
{
    /**
     * @brief An action that represents activating an ability.
     * @class ActivateAbilityAction
     *
     * @implements IAction
     */
    class ActivateAbilityAction : public IAction
    {
    public:
        /**
         * Constructs a new activate ability action.
         * @param ability The ability to activate.
         * @param context The context for the ability's execution.
         */
        ActivateAbilityAction(const abilities::IAbility *ability,
                              const abilities::AbilityContext &context)
            : m_ability(ability), m_context(context)
        {
        }

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) override;

    private:
        const abilities::IAbility *m_ability;
        abilities::AbilityContext m_context;
    };
} // namespace dandan::core

#endif
