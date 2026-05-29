#ifndef DANDAN_PREVENTION_MANAGER_H
#define DANDAN_PREVENTION_MANAGER_H

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
        /** Subscribe a prevention effect.
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

        /** Unsubscribe the prevention effect.
         * @param effect The prevention effect to unsubscribe.
         */
        void unsubscribe(const effects::IPreventionEffect *effect);

        /** Check if an action is prevented.
         * @param action The action to check.
         * @param game The game instance.
         * @return True if the action is prevented by a prevention effect, false
         * otherwise.
         */
        [[nodiscard]] bool isPrevented(const IAction &action,
                                       const Game &game) const;

    private:
        using PreventionList =
            std::vector<std::unique_ptr<effects::IPreventionEffect>>;

        PreventionList m_global_preventions;
        std::unordered_map<int, PreventionList> m_player_preventions;
        std::unordered_map<int, PreventionList> m_card_preventions;

        static void removeFromPreventionList(
            PreventionList &list, const effects::IPreventionEffect *effect);

        static bool isPreventedByPreventionList(const PreventionList &list,
                                                const IAction &action,
                                                const Game &game);
    };
} // namespace dandan::core

#endif
