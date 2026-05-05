#ifndef DANDAN_GAME_H
#define DANDAN_GAME_H

#include "Deck.h"
#include "EventManager.h"
#include "Player.h"
#include "Stack.h"
#include "dandan/core/PreventionManager.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/phases/IPhase.h"
#include <array>
#include <memory>

namespace dandan::core
{
    inline void printCards(const std::vector<std::unique_ptr<Card>> &cards)
    {
        std::cout << "[";
        for (const auto &card : cards)
        {
            std::cout << card->getName() << ", ";
        }
        std::cout << "]\n";
    }

    const static int AMOUNT_PLAYERS{2};

    const static std::array<std::string, AMOUNT_PLAYERS> DEFAULT_NAMES{
        std::array<std::string, AMOUNT_PLAYERS>{"Player 1", "Player 2"}};

    const static int CLEAR_SCREEN_LINES{10};

    class Game
    {
    public:
#ifdef DANDAN_BUILD_SERIALIZE
        Game();
#endif

        explicit Game(Deck &&deck);

        [[nodiscard]] const Player &getActivePlayer() const
        {
            return m_players.at(m_active_player_index);
        }

        [[nodiscard]] Player &getActivePlayer()
        {
            return m_players.at(m_active_player_index);
        }

        [[nodiscard]] const Player &getNonActivePlayer() const
        {
            return m_players.at(1 - m_active_player_index);
        }

        [[nodiscard]] Player &getNonActivePlayer()
        {
            return m_players.at(1 - m_active_player_index);
        }

        [[nodiscard]] Deck &getDeck()
        {
            return m_deck;
        }

        [[nodiscard]] EventManager &getEventManager()
        {
            return m_event_manager;
        }

        [[nodiscard]] const EventManager &getEventManager() const
        {
            return m_event_manager;
        }

        void changePhase(std::unique_ptr<IPhase> &&phase)
        {
            m_phase = std::move(phase);
        }

        void setDeck(Deck &&deck)
        {
            m_deck = std::move(deck);
        }

        [[nodiscard]] bool isFirstTurn() const
        {
            return m_first_turn;
        }

        void run();

        void render() const;

        // TODO: this is a temporary solution, should be replaced with proper
        // turn structure and phase handling
        void passTurn()
        {
            changePhase(std::make_unique<EndingPhase>(this));
            m_active_player_index = 1 - m_active_player_index;
            changePhase(std::make_unique<BeginningPhase>(this));
        }

        void handlePhase()
        {
            if (m_phase)
            {
                auto next_phase = m_phase->handle();
                m_phase = std::move(next_phase);
                // TODO: this is a temporary solution to the first turn rule, we
                // should implement this as a prevention effect instead of
                // hardcoding it here
                m_first_turn = false;
            }
        }

        [[nodiscard]] bool isActionPrevented(const IAction &action) const
        {
            return m_prevention_manager.isPrevented(action, *this);
        }

    private:
        std::array<Player, AMOUNT_PLAYERS> m_players{
            Player(DEFAULT_NAMES.at(0)), Player(DEFAULT_NAMES.at(1))};
        int m_active_player_index{};
        Deck m_deck;
        Stack m_stack;
        // TODO: consider merging these into one manager class that handles both
        // events and prevention effects
        EventManager m_event_manager;
        PreventionManager m_prevention_manager;
        std::unique_ptr<IPhase> m_phase;
        bool m_first_turn{true};
        // Graveyard m_graveyard;

        void GameSetup();

        static void clearScreen();
    };
} // namespace dandan::core

#endif // DANDAN_GAME_H