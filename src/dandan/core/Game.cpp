#include "dandan/core/Game.h"

namespace dandan::core
{
    Game::Game()
    {
        m_active_player.setHand(Hand(m_deck.draw(STARTING_HAND_SIZE)));
        m_non_active_player.setHand(Hand(m_deck.draw(STARTING_HAND_SIZE)));
    }

    void Game::printCards() const
    {
        std::cout << "Cards in deck:\n";
        for (const auto &card : m_deck.getCards())
        {
            std::cout << *card << '\n';
        }

        std::cout << "\nCards in hand for active player:\n";
        for (const auto &card : m_active_player.getHand().getCards())
        {
            std::cout << *card << '\n';
        }

        std::cout << "\nCards in hand for non-active player:\n";
        for (const auto &card : m_non_active_player.getHand().getCards())
        {
            std::cout << *card << '\n';
        }

        std::cout << "\nCards on battlefield for active player:\n";
        for (const auto &card :
             m_active_player.getBattlefield().getPermanents())
        {
            std::cout << *card << '\n';
        }
    }
} // namespace dandan::core