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
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/phases/IPhase.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <array>
#include <cassert>
#include <iostream>
#include <memory>

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
        [[nodiscard]] const Player &getPlayer(PlayerID player_id) const
        {
            return m_players.at(player_id.id());
        }

        /** Gets a player from the game accosiated with the given ID mutably.
         * @param player_id The ID of the player to get.
         * @return A reference to the player at the specified ID.
         */
        [[nodiscard]] Player &getPlayer(PlayerID player_id)
        {
            return m_players.at(player_id.id());
        }

        /** Gets all players in the game immutably.
         * @return A const reference to the array of players.
         */
        [[nodiscard]] const std::array<Player, AMOUNT_PLAYERS> &getPlayers()
            const
        {
            return m_players;
        }

        /** Gets all players in the game mutably.
         * @return A reference to the array of players.
         */
        [[nodiscard]] std::array<Player, AMOUNT_PLAYERS> &getPlayers()
        {
            return m_players;
        }

        /** Gets the current active player immutably.
         * @return A const reference to the active player.
         */
        [[nodiscard]] const Player &activePlayer() const
        {
            return m_players.at(m_active_player_index);
        }

        /** Gets the current active player mutably.
         * @return A reference to the active player.
         */
        [[nodiscard]] Player &activePlayer()
        {
            return m_players.at(m_active_player_index);
        }

        [[nodiscard]] PlayerID activePlayerID() const
        {
            return PlayerID::fromInt(m_active_player_index);
        }

        /** Gets the non-active player immutably.
         * @return A const reference to the non-active player.
         */
        [[nodiscard]] const Player &nonActivePlayer() const
        {
            return m_players.at(1 - m_active_player_index);
        }

        /** Gets the non-active player mutably.
         * @return A reference to the non-active player.
         */
        [[nodiscard]] Player &nonActivePlayer()
        {
            return m_players.at(1 - m_active_player_index);
        }

        /** Gets the next player ID in turn order.
         * @param player_id The ID of the current player.
         * @return The ID of the next player.
         */
        [[nodiscard]] PlayerID getNextPlayerID(PlayerID player_id) const
        {
            return m_players.at((player_id.id() + 1) % AMOUNT_PLAYERS).getID();
        }

        [[nodiscard]] std::vector<core::Target> getValidTargets(
            core::ExecutionContext exec_ctx, core::TargetType type,
            Controller controller = Controller::Any) const;

        /** Gets the library mutably.
         * @return A reference to the library.
         */
        [[nodiscard]] Library &library()
        {
            return m_library;
        }

        [[nodiscard]] const Library &library() const
        {
            return m_library;
        }

        /** Gets the stack mutably.
         * @return A reference to the stack.
         */
        [[nodiscard]] Stack &stack()
        {
            return m_stack;
        }

        /** Gets the stack immutably.
         * @return A const reference to the stack.
         */
        [[nodiscard]] const Stack &stack() const
        {
            return m_stack;
        }

        /** Gets the graveyard mutably.
         * @return A reference to the graveyard.
         */
        [[nodiscard]] Graveyard &graveyard()
        {
            return m_graveyard;
        }

        /** Gets the graveyard immutably.
         * @return A const reference to the graveyard.
         */
        [[nodiscard]] const Graveyard &graveyard() const
        {
            return m_graveyard;
        }

        /** Gets the exile mutably.
         * @return A reference to the exile.
         */
        [[nodiscard]] Exile &exile()
        {
            return m_exile;
        }

        /** Gets the exile immutably.
         * @return A const reference to the exile.
         */
        [[nodiscard]] const Exile &exile() const
        {
            return m_exile;
        }

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

        void addEndOfTurnEffect(std::unique_ptr<effects::IOneShotEffect> effect)
        {
            std::cout << "added an end of turn effect\n";
            m_end_of_turn_effects.push_back(std::move(effect));
        }

        void applyEndOfTurnEffects(const ExecutionContext &exec_ctx)
        {
            for (const auto &effect : m_end_of_turn_effects)
            {
                std::cout << "Applying end of turn effect\n";
                // TODO: handle end of turn events
                static_cast<void>(effect->apply(exec_ctx));
            }
            m_end_of_turn_effects.clear();
        }

        /** Passes the turn to the next player.
         */
        void passTurn(const ExecutionContext &exec_ctx)
        {
            changePhase(std::make_unique<EndingPhase>(exec_ctx));
            m_active_player_index = 1 - m_active_player_index;
            m_first_turn = false;
            changePhase(std::make_unique<BeginningPhase>(exec_ctx));
        }

        /** Handles the current phase and transitions to the next phase.
         */
        void handlePhase()
        {
            assert(m_phase &&
                   "Phase should never be null during handlePhase()");
            auto next_phase = m_phase->handle();
            activePlayer().manaPool().empty();
            nonActivePlayer().manaPool().empty();
            m_phase = std::move(next_phase);
        }

        /** Changes the current phase.
         * @param phase The new phase.
         */
        void changePhase(std::unique_ptr<IPhase> &&phase)
        {
            m_phase = std::move(phase);
        }

        /** Checks if it is the first turn of the first player.
         * @return True if it is the first turn, false otherwise.
         */
        [[nodiscard]] bool isFirstTurn() const
        {
            return m_first_turn;
        }

        /** Gets the current phase.
         * @return A reference to the current phase.
         */
        [[nodiscard]] std::unique_ptr<IPhase> &phase()
        {
            return m_phase;
        }
        /** Prints the names and IDs of the specified cards.
         * @param card_ids The IDs of the cards to print.
         */
        void printCards(const std::vector<CardID> &card_ids,
                        const CardRegistry &card_registry) const
        {
            std::cout << "[";
            for (const auto &card_id : card_ids)
            {
                const auto *card = card_registry[card_id];
                std::cout << card->getData().name << "("
                          << "CardID: " << card->getID().getID() << ", ";
                std::cout << "#Abilities: "
                          << card->getCurrentAbilities().size() << ") ";
            }
            std::cout << "]\n";
        }
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
