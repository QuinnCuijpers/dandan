#include "dandan/core/PreventionManager.h"
#include "dandan/core/Game.h"
#include <algorithm>
#include <memory>
#include <variant>

namespace dandan::core
{
    void PreventionManager::subscribe(
        std::unique_ptr<effects::IPreventionEffect> effect)
    {
        m_global_preventions.push_back(std::move(effect));
    }

    void PreventionManager::subscribe(
        PlayerID player, std::unique_ptr<effects::IPreventionEffect> effect)
    {
        m_player_preventions[player.id()].push_back(std::move(effect));
    }

    void PreventionManager::subscribe(
        CardID card, std::unique_ptr<effects::IPreventionEffect> effect)
    {
        m_card_preventions[card.getID()].push_back(std::move(effect));
    }

    void PreventionManager::removeFromPreventionList(
        PreventionList &list, const effects::IPreventionEffect *effect)
    {
        list.erase(
            std::remove_if(
                list.begin(), list.end(),
                [effect](const std::unique_ptr<effects::IPreventionEffect>
                             &candidate) { return candidate.get() == effect; }),
            list.end());
    }

    void PreventionManager::unsubscribe(
        const effects::IPreventionEffect *effect)
    {

        removeFromPreventionList(m_global_preventions, effect);

        for (auto player_it = m_player_preventions.begin();
             player_it != m_player_preventions.end();)
        {
            removeFromPreventionList(player_it->second, effect);
            if (player_it->second.empty())
            {
                player_it = m_player_preventions.erase(player_it);
            }
            else
            {
                ++player_it;
            }
        }

        for (auto card_it = m_card_preventions.begin();
             card_it != m_card_preventions.end();)
        {
            removeFromPreventionList(card_it->second, effect);
            if (card_it->second.empty())
            {
                card_it = m_card_preventions.erase(card_it);
            }
            else
            {
                ++card_it;
            }
        }
    }

    void PreventionManager::unsubscribe(CardID card_id)
    {
        m_card_preventions.erase(card_id.getID());
    }

    bool PreventionManager::isPreventedByPreventionList(
        const PreventionList &list, const IAction &action, const Game &game)
    {
        return std::any_of(list.begin(), list.end(),
                           [&action, &game](const auto &effect)
                           { return effect->prevents(action, game); });
    }

    bool PreventionManager::isPrevented(const IAction &action,
                                        const Game &game) const
    {

        std::cout << "Checking global-scoped preventions\n";
        if (isPreventedByPreventionList(m_global_preventions, action, game))
        {
            return true;
        }

        const auto actor = action.getActor();

        if (std::holds_alternative<PlayerID>(actor))
        {
            std::cout << "Checking player-scoped prevention effects for player "
                      << std::get<PlayerID>(actor).id() << '\n';
            const auto player_id = std::get<PlayerID>(actor).id();
            if (const auto player_it = m_player_preventions.find(player_id);
                player_it != m_player_preventions.end() &&
                isPreventedByPreventionList(player_it->second, action, game))
            {
                return true;
            }
        }
        else if (std::holds_alternative<CardID>(actor))
        {
            std::cout << "Checking card-scoped prevention effects for card "
                      << std::get<CardID>(actor).getID() << '\n';
            const auto card_id = std::get<CardID>(actor).getID();
            if (const auto card_it = m_card_preventions.find(card_id);
                card_it != m_card_preventions.end() &&
                isPreventedByPreventionList(card_it->second, action, game))
            {
                return true;
            }
        }
        return false;
    }
} // namespace dandan::core