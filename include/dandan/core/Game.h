#ifndef DANDAN_GAME_H
#define DANDAN_GAME_H

#include "EventManager.h"
#include "Player.h"
#include "ReplacementManager.h"
#include "Stack.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/ConditionManager.h"
#include "dandan/core/Constants.h"
#include "dandan/core/Exile.h"
#include "dandan/core/Graveyard.h"
#include "dandan/core/Library.h"
#include "dandan/core/PreventionManager.h"
#include "dandan/core/PriorityManager.h"
#include "dandan/core/SBAManager.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/phases/IPhase.h"
#include <filesystem>
#include <istream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace dandan::core
{
    // TODO: implement builder pattern to make it easier to build
    // OR make the game setup be a function that needs to be called explicitly

    /** @brief A class that represents the game state.
     * @class Game
     */
    class Game
    {

    public:
#ifdef DANDAN_SERIALIZE
        Game();
#endif

        /** Constructs a game with the given input stream.
         * @param input The input stream to initialize the game with.
         * @return The constructed game instance.
         */
        static Game withIstream(std::istream &input);

        /** Constructs a game with the given cards.
         * @param cards The cards vector to initialize the game with.
         * @return The constructed game instance.
         */
        static Game withCards(std::vector<Card> cards, bool shuffle = true);

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

        /** Gets the library mutably.
         * @return A reference to the library.
         */
        [[nodiscard]] Library &library()
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

        /** Gets the event manager mutably.
         * @return A reference to the event manager.
         */
        [[nodiscard]] EventManager &eventManager()
        {
            return m_event_manager;
        }

        /** Gets the event manager immutably.
         * @return A const reference to the event manager.
         */
        [[nodiscard]] const EventManager &eventManager() const
        {
            return m_event_manager;
        }

        /** Gets the replacement manager mutably.
         * @return A reference to the replacement manager.
         */
        [[nodiscard]] ReplacementManager &replacementManager()
        {
            return m_replacement_manager;
        }

        /** Gets the replacement manager immutably.
         * @return A const reference to the replacement manager.
         */
        [[nodiscard]] const ReplacementManager &replacementManager() const
        {
            return m_replacement_manager;
        }

        /** Gets the prevention manager mutably.
         * @return A reference to the prevention manager.
         */
        [[nodiscard]] PreventionManager &preventionManager()
        {
            return m_prevention_manager;
        }

        /** Gets the prevention manager immutably.
         * @return A const reference to the prevention manager.
         */
        [[nodiscard]] const PreventionManager &preventionManager() const
        {
            return m_prevention_manager;
        }

        /** Gets the SBA manager mutably.
         * @return A reference to the SBA manager.
         */
        [[nodiscard]] SBAManager &sbaManager()
        {
            return m_sba_manager;
        }

        /** Gets the SBA manager immutably.
         * @return A const reference to the SBA manager.
         */
        [[nodiscard]] const SBAManager &sbaManager() const
        {
            return m_sba_manager;
        }

        /** Gets the priority manager mutably.
         * @return A reference to the priority manager.
         */
        [[nodiscard]] PriorityManager &priorityManager()
        {
            return m_priority_manager;
        }

        /** Gets the priority manager immutably.
         * @return A const reference to the priority manager.
         */
        [[nodiscard]] const PriorityManager &priorityManager() const
        {
            return m_priority_manager;
        }

        /** Gets the condition manager mutably.
         * @return A reference to the condition manager.
         */
        [[nodiscard]] ConditionManager &conditionManager()
        {
            return m_condition_manager;
        }

        /** Gets the condition manager immutably.
         * @return A const reference to the condition manager.
         */
        [[nodiscard]] const ConditionManager &conditionManager() const
        {
            return m_condition_manager;
        }

        /** Gets the input stream mutably.
         * @return A reference to the input stream.
         */
        [[nodiscard]] std::istream &istream()
        {
            return *m_input;
        }

        /** Sets the input stream.
         * @param istream The input stream to set.
         */
        void setIstream(std::istream &istream)
        {
            m_input = &istream;
        }

        /** Changes the current phase.
         * @param phase The new phase.
         */
        void changePhase(std::unique_ptr<IPhase> &&phase)
        {
            m_phase = std::move(phase);
        }

        /** Sets the library.
         * @param library The library to set.
         */
        void setLibrary(Library &&library)
        {
            m_library = std::move(library);
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

        /** Runs the game loop.
         */
        void run();

        /** Prints the names and IDs of the specified cards.
         * @param card_ids The IDs of the cards to print.
         */
        void printCards(const std::vector<CardID> &card_ids) const
        {
            std::cout << "[";
            for (const auto &card_id : card_ids)
            {
                const auto *card = getCardByID(card_id);
                if (card != nullptr)
                {
                    std::cout << card->getData().getName() << "("
                              << "CardID: " << card->getID().getID() << ", ";
                    std::cout << "Zone: " << card->getZone() << ") ";
                }
            }
            std::cout << "]\n";
        }

        /** Renders the game state.
         */
        void render() const;

        // TODO: this is a temporary solution, should be replaced with proper
        // turn structure and phase handling
        /** Passes the turn to the next player.
         */
        void passTurn()
        {
            changePhase(std::make_unique<EndingPhase>(*this));
            m_active_player_index = 1 - m_active_player_index;
            m_first_turn = false;
            changePhase(std::make_unique<BeginningPhase>(*this));
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

        /** Checks if an action is prevented.
         * @param action The action to check.
         * @return True if the action is prevented, false otherwise.
         */
        [[nodiscard]] bool isActionPrevented(const IAction &action) const
        {
            return m_prevention_manager.isPrevented(action, *this);
        }

        /** Gets a card by its ID immutably.
         * @param card_id The ID of the card to get.
         * @return A pointer to the card if found, throws otherwise.
         */
        [[nodiscard]] const Card *getCardByID(CardID card_id) const;

        /** Gets a card by int id immutably.
         * @param card_id The ID of the card to get.
         * @return A pointer to the card if found, throws otherwise.
         */
        [[nodiscard]] const Card *getCardByID(int card_id) const
        {
            return getCardByID(CardID::fromInt(card_id));
        }

        /** Gets a card by int mutably.
         * @param card_id The ID of the card to get.
         * @return A pointer to the card if found, throws otherwise.
         */
        [[nodiscard]] Card *getCardByID(CardID card_id);

        /** Gets a card by int id mutably.
         * @param card_id The ID of the card to get.
         * @return A pointer to the card if found, throws otherwise.
         */
        [[nodiscard]] Card *getCardByID(int card_id);

        /** Clears the card from its current zone.
         * @param player The player whose card is to be cleared.
         * @param card The card to clear.
         */
        void moveCardFromZone(Player &player, const Card &card);

        /** Quits the game for the specified player.
         * @param player The player who is quitting the game.
         */
        void quit(const Player &player);

    private:
        std::array<Player, AMOUNT_PLAYERS> m_players{
            Player(DEFAULT_NAMES.at(0)), Player(DEFAULT_NAMES.at(1))};
        int m_active_player_index{};
        Library m_library;
        Stack m_stack;
        Exile m_exile;

        EventManager m_event_manager;
        PreventionManager m_prevention_manager;
        ReplacementManager m_replacement_manager;
        PriorityManager m_priority_manager{m_players.at(0).getID()};
        ConditionManager m_condition_manager;
        SBAManager m_sba_manager;

        std::unique_ptr<IPhase> m_phase;
        std::istream *m_input{&std::cin};
        // stable container for all cards in the game
        std::deque<Card> m_cards;
        // map from card ID to pointer to card in m_cards for O(1) access to
        // cards by ID
        std::unordered_map<CardID, Card *> m_card_map;
        std::filesystem::path m_card_data_path{DANDAN_DECKLIST};
        bool m_first_turn{true};
        Graveyard m_graveyard;

        explicit Game(std::istream &input, bool shuffle = true);
        explicit Game(std::vector<Card> cards, bool shuffle = true);

        void GameSetup(bool shuffle = true);

        void loadCards(const std::filesystem::path &path);

        static void clearScreen();
    };
} // namespace dandan::core

#endif // DANDAN_GAME_H
