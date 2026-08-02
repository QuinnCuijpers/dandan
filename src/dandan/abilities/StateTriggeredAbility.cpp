#include "dandan/abilities/StateTriggeredAbility.h"

namespace dandan::abilities
{
    StateTriggeredAbility::StateTriggeredAbility(
        std::unique_ptr<conditions::ICondition> condition,
        std::unique_ptr<effects::IOneShotEffectDefinition> effect)
        : m_condition(std::move(condition)), m_effect(std::move(effect))
    {
    }

    /** Create an effect instance for this ability.
     * @param game The game instance.
     * @param context The ability context.
     * @return The created effect instance.
     */
    [[nodiscard]] std::unique_ptr<effects::IOneShotEffect>
    StateTriggeredAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        return m_effect->bind(game,
                              effects::EffectContext(context.source_card_id,
                                                     context.controller_id));
    }

    /** Get the condition for the ability as a const pointer
     * @return The condition for the ability
     */
    [[nodiscard]] const conditions::ICondition *StateTriggeredAbility::
        condition() const
    {
        return m_condition.get();
    }

    /** Get the condition for the ability as a mutable pointer
     * @return The condition for the ability
     */
    [[nodiscard]] conditions::ICondition *StateTriggeredAbility::condition()
    {
        return m_condition.get();
    }

    /** Get the effect of the ability
     * @return The effect of the ability
     */
    [[nodiscard]] const effects::IOneShotEffectDefinition *
    StateTriggeredAbility::getEffect() const
    {
        return m_effect.get();
    }

} // namespace dandan::abilities
