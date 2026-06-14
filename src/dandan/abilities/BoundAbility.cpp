#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"

namespace dandan::abilities
{
    core::CardID BoundAbility::sourceCard() const
    {
        return m_source_card->getID();
    }

    [[nodiscard]] core::PlayerID BoundAbility::sourcePlayer() const
    {
        return m_source_card->getControllerID();
    }

    /** Create an effect instance for this ability.
     * @param game The game instance.
     * @return The created effect instance.
     */
    [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> BoundAbility::
        createEffect(core::Game &game) const
    {
        AbilityContext context{m_source_card->getID(),
                               m_source_card->getControllerID(),
                               m_chosen_mode_index};
        auto effect{m_definition->createEffect(game, context)};
        return effect;
    }

    AbilityContext BoundAbility::getContext() const
    {
        return {sourceCard(), sourcePlayer(), m_chosen_mode_index,
                m_text_replacement};
    }
} // namespace dandan::abilities