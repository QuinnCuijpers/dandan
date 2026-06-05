#include "dandan/core/EventManager.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void EventManager::subscribe(const Card &card)
    {
        for (const auto &ability : card.getData().getAbilities())
        {
            if (const auto *triggered =
                    dynamic_cast<const abilities::EventTriggeredAbility *>(
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
        auto current_subscribers = std::vector<CardID>{};
        for (const auto &[card_id, abilities] : m_subscribers)
        {
            current_subscribers.push_back(card_id);
        }

        for (const auto &card_id : current_subscribers)
        {
            auto iter = m_subscribers.find(card_id);
            if (iter ==
                m_subscribers
                    .end()) // card was unsubscribed during event processing
            {
                continue;
            }

            for (const auto *ability : iter->second)
            {
                auto *card{game.getCardByID(card_id)};
                auto ability_context{abilities::AbilityContext{
                    card->getID(), card->getControllerID()}};
                if (ability->appliesTo(event, ability_context))
                {
                    game.stack().push(
                        abilities::BoundAbility{*ability, ability_context});
                }
            }
        }
    }
} // namespace dandan::core