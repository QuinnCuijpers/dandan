#ifndef DANDAN_GAME_H
#define DANDAN_GAME_H

#include "Player.h"
#include "Stack.h"
#include "Target.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardData.h"
#include "dandan/core/CardID.h"
#include "dandan/core/CardRegistry.h"
#include "dandan/core/Constants.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Exile.h"
#include "dandan/core/Graveyard.h"
#include "dandan/core/Library.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/PriorityManager.h"
#include "dandan/core/SBAManager.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/core/engine/ConditionManager.h"
#include "dandan/core/engine/PreventionManager.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/phases/IPhase.h"
#include "engine/EventManager.h"
#include "engine/ReplacementManager.h"
#include <istream>
#include <memory>
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
        explicit Game(const std::filesystem::path &path);
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

        CardRegistry &cardRegistry()
        {
            return m_card_registry;
        }

        std::vector<CardID> cards() const
        {
            return m_card_registry.card_ids();
        }

        void addEndOfTurnEffect(std::unique_ptr<effects::IOneShotEffect> effect)
        {
            std::cout << "added end of turn effect: " << typeid(effect).name()
                      << '\n';
            m_end_of_turn_effects.push_back(std::move(effect));
        }

        void applyEndOfTurnEffects()
        {
            for (const auto &effect : m_end_of_turn_effects)
            {
                std::cout << "Applying end of turn effect\n";
                // TODO: handle end of turn events
                static_cast<void>(
                    effect->apply(ExecutionContext{*this, m_card_registry}));
            }
            m_end_of_turn_effects.clear();
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
                const auto *card = m_card_registry[card_id];
                if (card != nullptr)
                {
                    std::cout << card->getData().name << "("
                              << "CardID: " << card->getID().getID() << ", ";
                    std::cout
                        << "#Abilities: " << card->getCurrentAbilities().size()
                        << ") ";
                }
            }
            std::cout << "]\n";
        }

        /** Renders the game state.
         */
        void render() const;

        /** Passes the turn to the next player.
         */
        void passTurn()
        {
            changePhase(std::make_unique<EndingPhase>(
                ExecutionContext{*this, m_card_registry}));
            m_active_player_index = 1 - m_active_player_index;
            m_first_turn = false;
            changePhase(std::make_unique<BeginningPhase>(
                ExecutionContext{*this, m_card_registry}));
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
        [[nodiscard]] bool isActionPrevented(const IAction &action)
        {
            return m_prevention_manager.isPrevented(action,
                                                    {*this, m_card_registry});
        }

        /** Clears the card from its current zone.
         * @param player The player whose card is to be cleared.
         * @param card The card to clear.
         */
        void moveCardFromZone(Player &player, const Card &card);

        void moveCardToZone(Card &card, Player &player, Zone zone);

        /** Quits the game for the specified player.
         * @param player The player who is quitting the game.
         */
        void quit(const Player &player) const;

        std::vector<core::Target> getValidTargets(
            core::TargetType type,
            Controller controller = Controller::Any) const;

        void handlePlay(const std::string &input);
        void handleActivate(const std::string &input);

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

        CardRegistry m_card_registry;

        std::vector<std::unique_ptr<effects::IOneShotEffect>>
            m_end_of_turn_effects;

        std::unique_ptr<IPhase> m_phase;
        std::istream *m_input{&std::cin};

        bool m_first_turn{true};
        Graveyard m_graveyard;

        explicit Game(std::istream &input, bool shuffle = true);
        explicit Game(std::vector<Card> cards, bool shuffle = true);

        void GameSetup(bool shuffle = true);

        std::vector<Target> getValidCreatures(
            Controller controller = Controller::Any) const;

        static void clearScreen();
    };
} // namespace dandan::core

#endif // DANDAN_GAME_H
