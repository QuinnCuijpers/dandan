#ifndef DANDAN_CONDITION_MANAGER_H
#define DANDAN_CONDITION_MANAGER_H

#include "dandan/abilities/StateTriggeredAbility.h"
#include "dandan/conditions/ICondition.h"
#include "dandan/core/CardID.h"
#include <iostream>
#include <unordered_map>
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