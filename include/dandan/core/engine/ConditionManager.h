#ifndef DANDAN_CONDITION_MANAGER_H
#define DANDAN_CONDITION_MANAGER_H

#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/StateTriggeredAbility.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/CardID.h"
#include "dandan/effects/EffectContext.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <unordered_map>
#include <vector>
// 603.8. Some triggered abilities trigger when a game state (such as a player
// controlling no permanents of a particular card type) is true, rather than
// triggering when an event occurs. These abilities trigger as soon as the game
// state matches the condition. They’ll go onto the stack at the next available
// opportunity. These are called state triggers. (Note that state triggers
// aren’t the same as state-based actions.) A state-triggered ability doesn’t
// trigger again until the ability has resolved, has been countered, or has
// otherwise left the stack. Then, if the object with the ability is still in
// the same zone and the game state still matches its trigger condition, the
// ability will trigger again. Example: A permanent’s ability reads, “Whenever
// you have no cards in hand, draw a card.” If its controller plays the last
// card from their hand, the ability will trigger once and won’t trigger again
// until it has left the stack. If its controller casts a spell that reads
// “Discard your hand, then draw that many cards,” the ability will trigger
// during the spell’s resolution because the player’s hand was momentarily
// empty.
namespace dandan::core
{
    /** @brief A record for tracking triggered abilities.
     * @struct TriggeredRecord
     */
    struct TriggeredRecord
    {
        /// pointer to the State Triggered ability. As this is a pointer to the
        /// static definition on CardData, we can be assured that it will remain
        /// valid as long as the card exists.
        abilities::BoundAbility *bound_ability;
        /// boolean representing whether or not a trigger condition has been
        /// satisfied since the last time SBA were checked.
        bool satisfied;
    };

    /** @brief A manager for handling game conditions and triggered abilities.
     * @class ConditionManager
     */
    class ConditionManager
    {
    public:
        /** @brief Add a state-triggered ability to the manager.
         * @param source The card ID of the source.
         * @param ability The state-triggered ability.
         */
        void addStateTriggeredAbility(abilities::BoundAbility *ability)
        {

            if (ability->type() == abilities::AbilityType::Type::StateTriggered)
            {
                std::cout << "Adding StateTriggered ability\n";
                auto source{ability->sourceCard()};
                auto triggered_record{TriggeredRecord{ability, false}};
                m_trigger_records[source].push_back(triggered_record);
            }
        }

        void removeStateTriggeredAbility(const abilities::BoundAbility &ability)
        {
            auto source{ability.sourceCard()};
            auto source_triggered_it{m_trigger_records.find(source)};
            if (source_triggered_it == m_trigger_records.end())
            {
                std::cout << "NO TRIGGER RECORD FOR " << source.getID() << '\n';
                return;
            }
            if (source_triggered_it->second.empty())
            {
                std::cout << "TRIGGER RECORD IS EMPTY\n";
                m_trigger_records.erase(source_triggered_it);
                return;
            }
            auto &source_abilities{m_trigger_records[source]};
            source_abilities.erase(
                std::remove_if(source_abilities.begin(), source_abilities.end(),
                               [&ability](const TriggeredRecord &record)
                               { return record.bound_ability == &ability; }),
                source_abilities.end());
        }

        /** @brief Remove all conditions associated with a card.
         * @param card_id The ID of the card.
         */
        void removeCardConditions(CardID card_id)
        {
            m_trigger_records.erase(card_id);
        }

        /** @brief Update the conditions for all tracked abilities.
         * @param game The game instance.
         */
        void checkConditions(const Game &game)
        {
            for (auto &[card_id, triggered_records] : m_trigger_records)
            {
                for (auto &triggered_record : triggered_records)
                {
                    const auto &underlying_ability{
                        triggered_record.bound_ability->definition()};

                    if (const auto *triggered_ability = dynamic_cast<
                            const abilities::StateTriggeredAbility *>(
                            &underlying_ability))
                    {
                        auto context{
                            triggered_record.bound_ability->getContext()};
                        effects::EffectContext effect_context{context};
                        bool currently_satisfied =
                            triggered_ability->condition()->isSatisfied(
                                game, effect_context);

                        if (currently_satisfied && !triggered_record.satisfied)
                        {
                            std::cout << "Condition for ability on card "
                                      << card_id.getID()
                                      << " is now satisfied\n";
                            triggered_record.satisfied = true;
                        }
                    }
                }
            }
        }

        std::size_t size() const
        {
            std::size_t total{};
            for (const auto &[card_id, vec] : m_trigger_records)
            {
                total += vec.size();
            }
            return total;
        }

        /** @brief Get the trigger records.
         * @return A const reference to the map of trigger records.
         */
        const std::unordered_map<CardID, std::vector<TriggeredRecord>> &
        getTriggerRecords() const
        {
            return m_trigger_records;
        }

    private:
        std::unordered_map<CardID, std::vector<TriggeredRecord>>
            m_trigger_records;
    };
} // namespace dandan::core

#endif