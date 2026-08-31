#ifndef DANDAN_GAME_H
#define DANDAN_GAME_H

#include "Player.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/CardRegistry.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/GameState.h"
#include "dandan/core/PriorityManager.h"
#include "dandan/core/SBAManager.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/core/engine/ConditionManager.h"
#include "dandan/core/engine/InputManager.h"
#include "dandan/core/engine/PreventionManager.h"
#include "dandan/core/phases/IPhase.h"
#include "engine/EventManager.h"
#include "engine/ReplacementManager.h"
#include <istream>
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

        /** Sets the input stream.
         * @param istream The input stream to set.
         */
        void setIstream(std::istream &istream)
        {
            m_input_manager.setInput(istream);
        }

        ExecutionContext execution_context()
        {
            return {
                m_game_state,       m_card_registry,      m_input_manager,
                m_event_manager,    m_prevention_manager, m_replacement_manager,
                m_priority_manager, m_condition_manager,  m_sba_manager};
        }

        /** Runs the game loop.
         */
        void run();

    private:
        GameState m_game_state;

        EventManager m_event_manager;
        PreventionManager m_prevention_manager;
        ReplacementManager m_replacement_manager;
        PriorityManager m_priority_manager;
        ConditionManager m_condition_manager;
        SBAManager m_sba_manager;
        InputManager m_input_manager;
        CardRegistry m_card_registry;

        explicit Game(std::istream &input, bool shuffle = true);
        explicit Game(std::vector<Card> cards, bool shuffle = true);

        void GameSetup(bool shuffle = true);
    };
} // namespace dandan::core

#endif // DANDAN_GAME_H
