#ifndef DANDAN_CONDITION_MANAGER_H
#define DANDAN_CONDITION_MANAGER_H

#include "dandan/abilities/StateTriggeredAbility.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/CardID.h"
#include <iostream>
#include <unordered_map>
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
    struct TriggeredRecord
    {
        // pointer to static ability on CardData
        abilities::StateTriggeredAbility *ability;
        bool satisfied;
    };

    class ConditionManager
    {
    public:
        void addStateTriggeredAbility(CardID source,
                                      abilities::StateTriggeredAbility *ability)
        {
            m_trigger_records[source] = {ability, false};
        }

        void checkConditions(const Game &game)
        {
            for (auto &[card_id, triggered_record] : m_trigger_records)
            {
                bool currently_satisfied =
                    triggered_record.ability->condition()->isSatisfied(game);
                if (currently_satisfied && !triggered_record.satisfied)
                {
                    std::cout << "Condition for ability on card "
                              << card_id.getID()
                              << " is now satisfied, triggering ability.\n";
                    triggered_record.satisfied = true;
                }
                else if (!currently_satisfied && triggered_record.satisfied)
                {
                    std::cout << "Condition for ability on card "
                              << card_id.getID()
                              << " is no longer satisfied.\n";
                    triggered_record.satisfied = false;
                }
            }
        }

        const std::unordered_map<CardID, TriggeredRecord> &getTriggerRecords()
            const
        {
            return m_trigger_records;
        }

    private:
        std::unordered_map<CardID, TriggeredRecord> m_trigger_records;
    };
} // namespace dandan::core

#endif