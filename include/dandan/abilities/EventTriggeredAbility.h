#ifndef DANDAN_EVENTTRIGGEREDABILITY_H
#define DANDAN_EVENTTRIGGEREDABILITY_H

#include "IAbility.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/triggers/ITrigger.h"
#include <memory>

namespace dandan::abilities
{
    /** @brief A triggered ability that activates when a specific trigger event
     * occurs.
     * @class EventTriggeredAbility
     *
     * @implements IAbility
     */
    class EventTriggeredAbility final : public IAbility
    {
    public:
        /** Constructor
         * @param trigger The trigger for the ability
         * @param effect The effect of the ability
         */
        EventTriggeredAbility(
            std::unique_ptr<dandan::triggers::ITrigger> trigger,
            std::unique_ptr<dandan::effects::IOneShotEffect> effect)
            : m_trigger(std::move(trigger)), m_effect(std::move(effect))
        {
        }

        /** Check if the triiggered ability applies to a given event and
         * context.
         * @param event The event to check.
         * @param context The ability context.
         * @return True if the ability applies, false otherwise.
         */
        [[nodiscard]] bool appliesTo(const events::IEvent &event,
                                     abilities::AbilityContext context) const
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

    private:
        std::unique_ptr<dandan::triggers::ITrigger> m_trigger;
        std::unique_ptr<dandan::effects::IOneShotEffect> m_effect;
    };
} // namespace dandan::abilities

#endif
