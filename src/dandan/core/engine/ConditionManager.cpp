#include "dandan/core/engine/ConditionManager.h"
#include "dandan/abilities/StateTriggeredAbility.h"
#include <algorithm>
#include <iostream>

namespace dandan::core
{
    void ConditionManager::addStateTriggeredAbility(
        abilities::BoundAbility *ability)
    {

        if (ability->type() == abilities::AbilityType::Type::StateTriggered)
        {
            std::cout << "Adding StateTriggered ability\n";
            auto source{ability->sourceCard()};
            auto triggered_record{TriggeredRecord{ability, false}};
            m_trigger_records[source].push_back(triggered_record);
        }
    }

    void ConditionManager::removeStateTriggeredAbility(
        const abilities::BoundAbility &ability)
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

    void ConditionManager::removeCardConditions(CardID card_id)
    {
        m_trigger_records.erase(card_id);
    }

    void ConditionManager::checkConditions(const Game &game)
    {
        for (auto &[card_id, triggered_records] : m_trigger_records)
        {
            for (auto &triggered_record : triggered_records)
            {
                const auto &underlying_ability{
                    triggered_record.bound_ability->definition()};

                if (const auto *triggered_ability =
                        dynamic_cast<const abilities::StateTriggeredAbility *>(
                            &underlying_ability))
                {
                    auto context{triggered_record.bound_ability->getContext()};
                    effects::EffectContext effect_context{context};
                    bool currently_satisfied =
                        triggered_ability->condition()->isSatisfied(
                            game, effect_context);

                    if (currently_satisfied && !triggered_record.satisfied)
                    {
                        std::cout << "Condition for ability on card "
                                  << card_id.getID() << " is now satisfied\n";
                        triggered_record.satisfied = true;
                    }
                }
            }
        }
    }

    std::size_t ConditionManager::size() const
    {
        std::size_t total{};
        for (const auto &[card_id, vec] : m_trigger_records)
        {
            total += vec.size();
        }
        return total;
    }

    const std::unordered_map<CardID, std::vector<TriggeredRecord>> &
    ConditionManager::getTriggerRecords() const
    {
        return m_trigger_records;
    }

} // namespace dandan::core
