#ifndef DANDAN_GAME_H
#define DANDAN_GAME_H

#include "Deck.h"
#include "EventManager.h"
#include "Player.h"
#include "ReplacementManager.h"
#include "Stack.h"
#include "dandan/core/PreventionManager.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/phases/IPhase.h"
#include <istream>
#include <memory>

namespace dandan::core
{
    inline void printCards(const std::vector<Card> &cards)
    {
        std::cout << "[";
        for (const auto &card : cards)
        {
            std::cout << card.getData().getName() << ", ";
        }
        std::cout << "]\n";
    }

    class Game
    {
    public:
#ifdef DANDAN_BUILD_SERIALIZE
        Game();
#endif

        explicit Game(Deck &&deck);
        static Game withIstream(std::istream &input);

        [[nodiscard]] const Player &activePlayer() const
        {
            return m_players.at(m_active_player_index);
        }

        [[nodiscard]] Player &activePlayer()
        {
            return m_players.at(m_active_player_index);
        }

        [[nodiscard]] const Player &nonActivePlayer() const
        {
            return m_players.at(1 - m_active_player_index);
        }

        [[nodiscard]] Player &nonActivePlayer()
        {
            return m_players.at(1 - m_active_player_index);
        }

        [[nodiscard]] Deck &deck()
        {
            return m_deck;
        }

        [[nodiscard]] Stack &stack()
        {
            return m_stack;
        }

        [[nodiscard]] EventManager &eventManager()
        {
            return m_event_manager;
        }

        [[nodiscard]] const EventManager &eventManager() const
        {
            return m_event_manager;
        }

        [[nodiscard]] ReplacementManager &replacementManager()
        {
            return m_replacement_manager;
        }

        [[nodiscard]] const ReplacementManager &replacementManager() const
        {
            return m_replacement_manager;
        }

        [[nodiscard]] std::istream &istream()
        {
            return *m_input;
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
            changePhase(std::make_unique<EndingPhase>(*this));
            m_active_player_index = 1 - m_active_player_index;
            m_first_turn = false;
            changePhase(std::make_unique<BeginningPhase>(*this));
        }

        void handlePhase()
        {
            if (m_phase)
            {
                auto next_phase = m_phase->handle();
                m_phase = std::move(next_phase);
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
        EventManager m_event_manager;
        PreventionManager m_prevention_manager;
        ReplacementManager m_replacement_manager;
        std::unique_ptr<IPhase> m_phase;
        std::istream *m_input{&std::cin};
        bool m_first_turn{true};
        // Graveyard m_graveyard;

        explicit Game(std::istream &input);

        void GameSetup();

        static void clearScreen();
    };
} // namespace dandan::core

#endif // DANDAN_GAME_H