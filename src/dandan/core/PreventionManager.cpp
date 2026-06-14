#include "dandan/core/engine/PreventionManager.h"
#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/StaticAbility.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include "dandan/core/PlayerID.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include "dandan/utils/overloadVisitor.h"
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <variant>

namespace dandan::core
{
    void PreventionManager::subscribe(
        std::unique_ptr<effects::IPreventionEffect> effect)
    {
        m_global_preventions.emplace_back(std::move(effect));
    }

    void PreventionManager::subscribe(
        PlayerID player, std::unique_ptr<effects::IPreventionEffect> effect)
    {
        m_player_preventions[player].emplace_back(std::move(effect));
    }

    void PreventionManager::subscribe(
        CardID card, std::unique_ptr<effects::IPreventionEffect> effect)
    {
        m_card_preventions[card].emplace_back(std::move(effect));
    }

    void PreventionManager::subscribe(abilities::BoundAbility &ability)
    {

        if (ability.type() == abilities::AbilityType::StaticPrevention)
        {
            if (const auto *staticAbility =
                    dynamic_cast<const abilities::StaticAbility *>(
                        &ability.definition()))
            {
                if (staticAbility->getType() !=
                    abilities::StaticAbility::Type::Prevention)
                {
                    throw std::runtime_error(
                        "Staticprevention ability has a static ability whose "
                        "type was not prevention");
                }

                if (dynamic_cast<const effects::IPreventionEffect *>(
                        staticAbility->getEffect()) != nullptr)
                {
                    m_global_preventions.emplace_back(&ability);
                }
            }
        }
    }

    void PreventionManager::subscribe(CardID card_id,
                                      abilities::BoundAbility &ability)
    {
        if (ability.type() == abilities::AbilityType::StaticPrevention)
        {
            if (const auto *staticAbility =
                    dynamic_cast<const abilities::StaticAbility *>(
                        &ability.definition()))
            {
                if (staticAbility->getType() !=
                    abilities::StaticAbility::Type::Prevention)
                {
                    throw std::runtime_error(
                        "Staticprevention ability has a static ability whose "
                        "type was not prevention");
                }

                if (dynamic_cast<const effects::IPreventionEffect *>(
                        staticAbility->getEffect()) != nullptr)
                {
                    m_card_preventions[card_id].emplace_back(&ability);
                }
            }
        }
    }

    void PreventionManager::subscribe(PlayerID player_id,
                                      abilities::BoundAbility &ability)
    {
        if (ability.type() == abilities::AbilityType::StaticPrevention)
        {
            if (const auto *staticAbility =
                    dynamic_cast<const abilities::StaticAbility *>(
                        &ability.definition()))
            {
                if (staticAbility->getType() !=
                    abilities::StaticAbility::Type::Prevention)
                {
                    throw std::runtime_error(
                        "Staticprevention ability has a static ability whose "
                        "type was not prevention");
                }

                if (dynamic_cast<const effects::IPreventionEffect *>(
                        staticAbility->getEffect()) != nullptr)
                {
                    m_player_preventions[player_id].emplace_back(&ability);
                }
            }
        }
    }

    void PreventionManager::removeFromPreventionList(
        PreventionList &list, const effects::IPreventionEffect *effect)
    {
        list.erase(std::remove_if(
                       list.begin(), list.end(),
                       [effect](const PreventionEffect &candidate)
                       {
                           return std::visit(
                               utils::overloaded{
                                   [&](const std::unique_ptr<
                                       effects::IPreventionEffect> &prevention)
                                   { return prevention.get() == effect; },
                                   [](const abilities::BoundAbility *)
                                   { return false; }},
                               candidate);
                       }),
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
        m_card_preventions.erase(card_id);
    }

    bool PreventionManager::isPreventedByPreventionList(
        const PreventionList &list, const IAction &action, Game &game)
    {
        for (const auto &prevention : list)
        {
            auto prevented{std::visit(
                utils::overloaded{
                    [&](const std::unique_ptr<effects::IPreventionEffect>
                            &prevention_effect)
                    { return prevention_effect->prevents(action, game); },
                    [&](const abilities::BoundAbility *ability)
                    {
                        if (const auto *static_ability =
                                dynamic_cast<const abilities::StaticAbility *>(
                                    &ability->definition()))
                        {
                            assert(static_ability->getType() ==
                                   abilities::StaticAbility::Type::Prevention);
                            if (const auto *prevention_effect = dynamic_cast<
                                    const effects::IPreventionEffect *>(
                                    static_ability->getEffect()))
                            {
                                return prevention_effect->prevents(
                                    action, game, ability->getContext());
                            }
                        }
                        // should be unreachable as only prevention effects are
                        // registered in this class
                        return false;
                    }},
                prevention)};
            if (prevented)
            {
                return true;
            }
        }
        return false;
    }

    bool PreventionManager::isPrevented(const IAction &action, Game &game) const
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
            const auto player_id = std::get<PlayerID>(actor);
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
            const auto card_id = std::get<CardID>(actor);
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