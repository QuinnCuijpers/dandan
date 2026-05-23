#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "IAbility.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/triggers/ITrigger.h"
#include <memory>

namespace dandan::abilities
{
    /** A triggered ability that activates when a specific trigger applies
     * @class TriggeredAbility
     *
     * @implements IAbility
     */
    class TriggeredAbility final : public IAbility
    {
    public:
        /** Constructor
         * @param trigger The trigger for the ability
         * @param effect The effect of the ability
         */
        TriggeredAbility(
            std::unique_ptr<dandan::triggers::ITrigger> trigger,
            std::unique_ptr<dandan::effects::IOneShotEffect> effect)
            : m_trigger(std::move(trigger)), m_effect(std::move(effect))
        {
        }

        [[nodiscard]] bool appliesTo(
            const events::IEvent &event,
            abilities::AbilityContext context) const override
        {
            return m_trigger->triggersOn(event, context);
        }

        /** Get the trigger for the ability as a const pointer
         * @return The trigger for the ability
         */
        [[nodiscard]] const dandan::triggers::ITrigger *trigger() const
        {
            return m_trigger.get();
        }

        /** Get the trigger for the ability as a mutable pointer
         * @return The trigger for the ability
         */
        [[nodiscard]] dandan::triggers::ITrigger *trigger()
        {
            return m_trigger.get();
        }

        /** Get the effect of the ability
         * @return The effect of the ability
         */
        [[nodiscard]] const dandan::effects::IOneShotEffect *getEffect() const
        {
            return m_effect.get();
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

        bool canActivate([[maybe_unused]] core::Game &game,
                         [[maybe_unused]] AbilityContext context) const override
        {
            return false;
        }

    private:
        std::unique_ptr<dandan::triggers::ITrigger> m_trigger;
        std::unique_ptr<dandan::effects::IOneShotEffect> m_effect;
    };
} // namespace dandan::abilities

#endif