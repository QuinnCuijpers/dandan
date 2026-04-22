#ifndef DANDAN_GAME_H
#define DANDAN_GAME_H

#include "Deck.h"
#include "EventManager.h"
#include "Player.h"
#include "Stack.h"

namespace dandan::core
{
    class Game
    {
    public:
        Game();

        [[nodiscard]] Player &getActivePlayer()
        {
            return m_active_player;
        }

        [[nodiscard]] const Player &getNonActivePlayer() const
        {
            return m_non_active_player;
        }

        void printCards() const;

    private:
        Player m_active_player;
        Player m_non_active_player;

        Deck m_deck;
        Stack m_stack;
        EventManager m_event_manager;
        // Graveyard m_graveyard;
    };
} // namespace dandan::core

#endif // DANDAN_GAME_H