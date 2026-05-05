#include "dandan/core/Game.h"
#include "dandan/conditions/StartingPlayerCondition.h"
#include "dandan/core/Player.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include <memory>
#include <random>
#include <string>

namespace dandan::core
{
    void Game::GameSetup()
    {

        auto no_draw_starting_player{
            std::make_unique<effects::DrawPreventionEffect>(
                std::make_unique<conditions::StartingPlayerCondition>())};
        m_prevention_manager.subscribe(std::move(no_draw_starting_player));

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

    void Game::run()
    {
        while (true)
        {
            while (m_phase != nullptr)
            {
                render();
                handlePhase();
            }
            std::cout << "Passing turn\n";
            m_first_turn = false;
            m_active_player_index =
                (m_active_player_index + 1) % AMOUNT_PLAYERS;
            changePhase(std::make_unique<BeginningPhase>(this));
        }
    }

    void Game::clearScreen()
    {
        std::cout << std::string(CLEAR_SCREEN_LINES, '\n');
    }

    void Game::render() const
    {
        // Render the full TUI
        clearScreen();

        // Player name and hand (top)
        std::cout << getNonActivePlayer().getName() << "'s Hand: ";
        printCards(getNonActivePlayer().getHand().getCards());
        std::cout << "\n";

        // Player's battlefield
        std::cout << getNonActivePlayer().getName() << "'s Battlefield: ";
        printCards(getNonActivePlayer().getBattlefield().getPermanents());
        std::cout << "\n\n"; // space between battlefields

        // Opponent's battlefield
        std::cout << getActivePlayer().getName() << "'s Battlefield: ";
        printCards(getActivePlayer().getBattlefield().getPermanents());
        std::cout << "\n";

        // Opponent's hand and name
        std::cout << getActivePlayer().getName() << "'s Hand: ";
        printCards(getActivePlayer().getHand().getCards());
        std::cout << "\n";
    }
} // namespace dandan::core