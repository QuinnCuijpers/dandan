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
        Game() = default;

        void printCards() const
        {
            std::cout << "Cards in deck:\n";
            for (const auto &card : m_deck.getCards())
            {
                std::cout << *card << '\n';
            }

            std::cout << "Cards in hand for active player:\n";
            for (const auto &card : m_active_player.getHand().getCards())
            {
                std::cout << *card << '\n';
            }

            std::cout << "Cards in hand for non-active player:\n";
            for (const auto &card : m_non_active_player.getHand().getCards())
            {
                std::cout << *card << '\n';
            }
        }

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