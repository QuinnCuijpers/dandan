#include "dandan/core/Game.h"
#include "dandan/core/Player.h"
#include "dandan/core/phases/BeginningPhase.h"

namespace dandan::core
{
    void Game::GameSetup()
    {
        // Randomize whom is starting player
        // TODO: Implement proper dice rolling to determine starting player
        // through gui
        if (std::rand() % 2 == 0)
        {
            std::swap(m_active_player, m_non_active_player);
        }

        std::cout << "Active player: " << m_active_player.getName() << '\n';
        std::cout << "Non-active player: " << m_non_active_player.getName()
                  << '\n';

        std::cout << m_deck.getCards().size() << " cards in deck\n";

        for (int i{}; i < STARTING_HAND_SIZE; ++i)
        {
            m_active_player.drawCard(m_deck);
            m_non_active_player.drawCard(m_deck);
        }
        std::cout << "Game constructed\n";

        std::cout << "Changing phase to beginning phase\n";
        changePhase(std::make_unique<BeginningPhase>(this));
    }
#ifdef DANDAN_BUILD_SERIALIZE
    Game::Game()
    {
        GameSetup();
    }
#endif

    Game::Game(Deck &&deck) : m_deck{std::move(deck)}
    {
        std::cout << "Game constructed with deck\n";
        std::cout << "Deck size: " << m_deck.getCards().size() << '\n';
        GameSetup();
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