#include "dandan/core/engine/EventManager.h"
#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/EventTriggeredAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include <algorithm>

namespace dandan::core
{
    void EventManager::subscribe(abilities::BoundAbility &ability)
    {
        if (ability.type() == abilities::AbilityType::Type::EventTriggered)
        {
            std::cout << "subscribing to event manager\n";
            std::cout << "New size: " << size() << '\n';
            m_subscribers[ability.sourceCard()].push_back(&ability);
        }
    }

    void EventManager::unsubscribe(const Card &card)
    {
        m_subscribers.erase(card.getID());
    }

    void EventManager::unsubscribe(const abilities::BoundAbility &ability)
    {
        auto source{ability.sourceCard()};
        if (m_subscribers.find(source) == m_subscribers.end())
        {
            return;
        }
        if (m_subscribers.at(source).empty())
        {
            return;
        }
        auto source_abilities{m_subscribers[source]};
        source_abilities.erase(
            std::remove_if(source_abilities.begin(), source_abilities.end(),
                           [&ability](auto *sub_ability)
                           { return sub_ability == &ability; }),
            source_abilities.end());
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
                auto ability_context{ability->getContext()};
                const auto &underlying_ability{ability->definition()};
                if (const auto *event_triggered_ability =
                        dynamic_cast<const abilities::EventTriggeredAbility *>(
                            &underlying_ability))
                {
                    if (event_triggered_ability->appliesTo(event,
                                                           ability_context))
                    {
                        std::cout << "Triggered ability put on stack\n";
                        auto *card{game.getCardByID(card_id)};
                        game.stack().push(abilities::BoundAbility{
                            *event_triggered_ability, card,
                            ability_context.chosen_mode_index,
                            ability_context.text_replacements});
                    }
                }
            }
        }
    }
} // namespace dandan::core