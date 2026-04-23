#include "dandan/core/Game.h"
#include "dandan/core/Player.h"

namespace dandan::core
{
    Game::Game()
    {
        for (int i{}; i < STARTING_HAND_SIZE; ++i)
        {
            m_active_player.drawCard(m_deck);
            m_non_active_player.drawCard(m_deck);
        }
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