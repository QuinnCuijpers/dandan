#ifndef DANDAN_PRIORITY_MANAGER_H
#define DANDAN_PRIORITY_MANAGER_H

#include "dandan/core/PlayerID.h"
namespace dandan::core
{

    class Game;

    /** @brief A class that manages the priority of players in the game.
     * @class PriorityManager
     */
    class PriorityManager
    {
        // 117.3. Which player has priority is determined by the following
        // rules:
        //
        //  117.3a The active player receives priority at the beginning of most
        //  steps and phases, after any turn-
        // based actions (such as drawing a card during the draw step; see rule
        // 703) have been dealt with and abilities that trigger at the beginning
        // of that phase or step have been put on the stack. No player receives
        // priority during the untap step. Players usually don’t get priority
        // during the cleanup step (see rule 514.3).
        //
        //  117.3b The active player receives priority after a spell or ability
        //  (other than a mana ability) resolves.
        //
        // 117.3c If a player has priority when they cast a spell, activate an
        // ability, or take a special action, that player receives priority
        // afterward.
        //
        //  117.3d If a player has priority and chooses not to take any actions,
        //  that player passes. If any mana is
        // in that player’s mana pool, they announce what mana is there. Then
        // the next player in turn order receives priority.

    public:
        /** Constructs a new priority manager with the specified starting
         * player.
         * @param starting_player The player ID of the player who starts with
         * priority.
         */
        explicit PriorityManager(PlayerID starting_player)
            : m_current_player_with_priority{starting_player},
              m_last_acted_player(starting_player)
        {
        }

        /** Gets the player ID of the player who currently has priority.
         * @return The player ID of the player with priority.
         */
        [[nodiscard]] PlayerID getPlayerWithPriority() const
        {
            return m_current_player_with_priority;
        }

        /** Sets the priority to the active player.
         * @param game The game object to get the active player from.
         */
        void setPriorityToPlayer(PlayerID player_id, Game &game);

        /** Passes priority to the next player in turn order.
         * @param game The game object to get the next player from.
         */
        void passPriority(Game &game);

    private:
        PlayerID m_current_player_with_priority;
        PlayerID m_last_acted_player;

        void handleStack(core::Game &game);
    };

} // namespace dandan::core
#endif // DANDAN_PRIORITY_MANAGER_H
