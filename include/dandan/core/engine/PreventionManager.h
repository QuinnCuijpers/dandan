#ifndef DANDAN_PREVENTION_MANAGER_H
#define DANDAN_PREVENTION_MANAGER_H

#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace dandan::core
{
    /** @brief The class that manages prevention effects.
     * @class PreventionManager
     */
    class PreventionManager
    {
    public:
        /** Subscribe a global-scoped prevention effect.
         * @param effect The prevention effect to subscribe.
         */
        void subscribe(std::unique_ptr<effects::IPreventionEffect> effect);

        /** Subscribe a player-scoped prevention effect.
         * @param player The player that owns the prevention effect.
         * @param effect The prevention effect to subscribe.
         */
        void subscribe(PlayerID player,
                       std::unique_ptr<effects::IPreventionEffect> effect);

        /** Subscribe a card-scoped prevention effect.
         * @param card The card that owns the prevention effect.
         * @param effect The prevention effect to subscribe.
         */
        void subscribe(CardID card,
                       std::unique_ptr<effects::IPreventionEffect> effect);

        void subscribe(abilities::BoundAbility &ability);

        void subscribe(CardID card_id, abilities::BoundAbility &ability);

        void subscribe(PlayerID player_id, abilities::BoundAbility &ability);

        /** Unsubscribe the prevention effect.
         * @param effect The prevention effect to unsubscribe.
         */
        void unsubscribe(const effects::IPreventionEffect *effect);

        /** Unsubscribe all prevention effects for a card.
         * @param card_id The ID of the card.
         */
        void unsubscribe(CardID card_id);

        void unsubscribe(const abilities::BoundAbility &ability);

        std::size_t size() const
        {
            return m_card_preventions.size() + m_global_preventions.size() +
                   m_player_preventions.size();
        }

        /** Check if an action is prevented.
         * @param action The action to check.
         * @param game The game instance. Game is treated as const but as bound
         * abilities need to create a copy of their effect and those could pay
         * costs, we cant mark it as const for now
         * @return True if the action is prevented by a prevention effect, false
         * otherwise.
         */
        [[nodiscard]] bool isPrevented(const IAction &action, Game &game) const;

    private:
        using PreventionEffect =
            std::variant<std::unique_ptr<effects::IPreventionEffect>,
                         abilities::BoundAbility *>;
        using PreventionList = std::vector<PreventionEffect>;

        // split into three do differentiate which scope they have
        PreventionList m_global_preventions;
        std::unordered_map<PlayerID, PreventionList> m_player_preventions;
        std::unordered_map<CardID, PreventionList> m_card_preventions;

        static void removeFromPreventionList(
            PreventionList &list, const effects::IPreventionEffect *effect);

        static void removeFromPreventionList(
            PreventionList &list, const abilities::BoundAbility &ability);

        // TODO: Game is used as const as there is no bound ability that has
        // a prevention effect that requires a cost to  create, but this
        // should be fixed at some point
        static bool isPreventedByPreventionList(const PreventionList &list,
                                                const IAction &action,
                                                Game &game);
    };
} // namespace dandan::core

#endif
