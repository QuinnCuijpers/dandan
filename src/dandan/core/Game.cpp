#include "dandan/core/Game.h"
#include "dandan/core/Player.h"
#include "dandan/core/phases/BeginningPhase.h"
#include <random>

namespace dandan::core
{
    void Game::GameSetup()
    {
        // Randomize whom is starting player
        // TODO: Implement proper dice rolling to determine starting player
        // through gui
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> dist(0, AMOUNT_PLAYERS - 1);

        int starting_player_index = dist(gen);
        m_active_player_index = starting_player_index;

        std::cout << "Active player: " << getActivePlayer().getName() << '\n';
        std::cout << "Non-active player: " << getNonActivePlayer().getName()
                  << '\n';

        for (int i{}; i < STARTING_HAND_SIZE; ++i)
        {
            getActivePlayer().drawCard(m_deck);
            getNonActivePlayer().drawCard(m_deck);
        }
        // TODO: Implement mulligan rules
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
        for (const auto &card : getActivePlayer().getHand().getCards())
        {
            std::cout << *card << '\n';
        }

        std::cout << "\nCards in hand for non-active player:\n";
        for (const auto &card : getNonActivePlayer().getHand().getCards())
        {
            std::cout << *card << '\n';
        }

        std::cout << "\nCards on battlefield for active player:\n";
        for (const auto &card :
             getActivePlayer().getBattlefield().getPermanents())
        {
            std::cout << *card << '\n';
        }
    }
} // namespace dandan::core