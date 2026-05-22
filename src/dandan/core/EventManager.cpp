#include "dandan/core/EventManager.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/TriggeredAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"

namespace dandan::core
{
    void EventManager::subscribe(const Card &card)
    {
        for (const auto &ability : card.getData().getAbilities())
        {
            if (const auto *triggered =
                    dynamic_cast<const abilities::TriggeredAbility *>(
                        ability.get()))
            {
                m_subscribers[card.getID()].push_back(triggered);
            }
        }
    }

    void EventManager::unsubscribe(const Card &card)
    {
        m_subscribers.erase(card.getID());
    }

    void EventManager::notify(const events::IEvent &event,
                              core::Game &game) const
    {
        for (const auto &[card_id, abilities] : m_subscribers)
        {
            for (const auto *ability : abilities)
            {
                auto ability_context{
                    abilities::AbilityContext{CardID{card_id}}};
                if (ability->appliesTo(event, ability_context))
                {
                    ability->createEffect(game, ability_context);
                }
            }
        }
    }
} // namespace dandan::core