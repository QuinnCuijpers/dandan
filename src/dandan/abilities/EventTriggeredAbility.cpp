#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

namespace dandan::abilities
{

    EventTriggeredAbility::EventTriggeredAbility(
        std::unique_ptr<dandan::triggers::ITrigger> trigger,
        std::unique_ptr<dandan::effects::IOneShotEffectDefinition> effect)
        : m_trigger(std::move(trigger)), m_effect(std::move(effect))
    {
    }

    [[nodiscard]] bool EventTriggeredAbility::appliesTo(
        const events::IEvent &event, abilities::AbilityContext context) const
    {
        return m_trigger->triggersOn(event, std::move(context));
    }

    /** Get the trigger for the ability as a const pointer
     * @return The trigger for the ability
     */
    [[nodiscard]] const dandan::triggers::ITrigger *EventTriggeredAbility::
        trigger() const
    {
        return m_trigger.get();
    }

    /** Get the trigger for the ability as a mutable pointer
     * @return The trigger for the ability
     */
    [[nodiscard]] dandan::triggers::ITrigger *EventTriggeredAbility::trigger()
    {
        return m_trigger.get();
    }

    /** Get the effect of the ability
     * @return The effect of the ability
     */
    [[nodiscard]] const dandan::effects::IOneShotEffectDefinition *
    EventTriggeredAbility::getEffect() const
    {
        return m_effect.get();
    }
    std::unique_ptr<effects::IOneShotEffect> EventTriggeredAbility::
        createEffect([[maybe_unused]] core::Game &game,
                     [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving triggered ability\n";
        return m_effect->bind(game,
                              effects::EffectContext(context.controller_id));
    }

} // namespace dandan::abilities
