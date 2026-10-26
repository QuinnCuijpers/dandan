#ifndef DANDAN_GAMESTATE_H
#define DANDAN_GAMESTATE_H

#include "dandan/core/CardRegistry.h"
#include "dandan/core/Constants.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Exile.h"
#include "dandan/core/Graveyard.h"
#include "dandan/core/Library.h"
#include "dandan/core/Player.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/Stack.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/phases/IPhase.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace dandan::core
{

    class GameState
    {
    public:
        GameState() = default;

        /** Gets a player from the game accosiated with the given ID immutably.
         * @param player_id The ID of the player to get.
         * @return A const reference to the player at the specified ID.
         */
        [[nodiscard]] const Player &getPlayer(PlayerID player_id) const;

        /** Gets a player from the game accosiated with the given ID mutably.
         * @param player_id The ID of the player to get.
         * @return A reference to the player at the specified ID.
         */
        [[nodiscard]] Player &getPlayer(PlayerID player_id);

        /** Gets all players in the game immutably.
         * @return A const reference to the array of players.
         */
        [[nodiscard]] const std::array<Player, AMOUNT_PLAYERS> &getPlayers()
            const;

        /** Gets all players in the game mutably.
         * @return A reference to the array of players.
         */
        [[nodiscard]] std::array<Player, AMOUNT_PLAYERS> &getPlayers();

        /** Gets the current active player immutably.
         * @return A const reference to the active player.
         */
        [[nodiscard]] const Player &activePlayer() const;

        /** Gets the current active player mutably.
         * @return A reference to the active player.
         */
        [[nodiscard]] Player &activePlayer();

        /** Gets the non-active player immutably.
         * @return A const reference to the non-active player.
         */
        [[nodiscard]] const Player &nonActivePlayer() const;

        /** Gets the non-active player mutably.
         * @return A reference to the non-active player.
         */
        [[nodiscard]] Player &nonActivePlayer();

        /** Gets the next player ID in turn order.
         * @param player_id The ID of the current player.
         * @return The ID of the next player.
         */
        [[nodiscard]] PlayerID getNextPlayerID(PlayerID player_id) const;

        [[nodiscard]] std::vector<core::Target> getValidTargets(
            core::ExecutionContext exec_ctx, core::TargetType type,
            Controller controller = Controller::Any) const;

        /** Gets the library mutably.
         * @return A reference to the library.
         */
        [[nodiscard]] Library &library();
        [[nodiscard]] const Library &library() const;

        /** Gets the stack mutably.
         * @return A reference to the stack.
         */
        [[nodiscard]] Stack &stack();
        /** Gets the stack immutably.
         * @return A const reference to the stack.
         */
        [[nodiscard]] const Stack &stack() const;

        /** Gets the graveyard mutably.
         * @return A reference to the graveyard.
         */
        [[nodiscard]] Graveyard &graveyard();
        /** Gets the graveyard immutably.
         * @return A const reference to the graveyard.
         */
        [[nodiscard]] const Graveyard &graveyard() const;

        /** Gets the exile mutably.
         * @return A reference to the exile.
         */
        [[nodiscard]] Exile &exile();
        /** Gets the exile immutably.
         * @return A const reference to the exile.
         */
        [[nodiscard]] const Exile &exile() const;

        /** Clears the card from its current zone.
         * @param player The player whose card is to be cleared.
         * @param card The card to clear.
         */
        void moveCardFromZone(Player &player, const Card &card);

        void moveCardToZone(Card &card, Player &player, Zone zone);

        static void handlePlay(const std::string &input,
                               ExecutionContext exec_ctx);
        static void handleActivate(const std::string &input,
                                   ExecutionContext exec_ctx);

        /** Quits the game for the specified player.
         * @param player The player who is quitting the game.
         */
        void quit(const Player &player) const;

        void addEndOfTurnEffect(
            std::unique_ptr<effects::IOneShotEffect> effect);

        void applyEndOfTurnEffects(const ExecutionContext &exec_ctx);

        /** Passes the turn to the next player.
         */
        void passTurn(const ExecutionContext &exec_ctx);

        /** Handles the current phase and transitions to the next phase.
         */
        void handlePhase();

        /** Changes the current phase.
         * @param phase The new phase.
         */
        void changePhase(std::unique_ptr<IPhase> &&phase);

        /** Checks if it is the first turn of the first player.
         * @return True if it is the first turn, false otherwise.
         */
        [[nodiscard]] bool isFirstTurn() const;

        /** Gets the current phase.
         * @return A reference to the current phase.
         */
        [[nodiscard]] std::unique_ptr<IPhase> &phase();
        /** Prints the names and IDs of the specified cards.
         * @param card_ids The IDs of the cards to print.
         */
        static void printCards(const std::vector<CardID> &card_ids,
                               const CardRegistry &card_registry);
        static void clearScreen();

        /** Renders the game state.
         */
        void render(const CardRegistry &card_registry) const;

    private:
        std::array<Player, AMOUNT_PLAYERS> m_players{
            Player(DEFAULT_NAMES.at(0)), Player(DEFAULT_NAMES.at(1))};
        int m_active_player_index{};

        Library m_library;
        Stack m_stack;
        Exile m_exile;
        Graveyard m_graveyard;

        std::unique_ptr<IPhase> m_phase;

        bool m_first_turn{true};
        std::vector<std::unique_ptr<effects::IOneShotEffect>>
            m_end_of_turn_effects;

        [[nodiscard]] std::vector<Target> getValidCreatures(
            ExecutionContext exec_ctx,
            Controller controller = Controller::Any) const;
    };
} // namespace dandan::core

#endif
