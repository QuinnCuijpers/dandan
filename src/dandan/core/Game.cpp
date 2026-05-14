#include "dandan/core/Game.h"
#include "dandan/conditions/StartingPlayerCondition.h"
#include "dandan/core/Player.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/log.h"
#include <functional>
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

        DLOGI << "Active player: " << activePlayer().getName() << '\n';
        DLOGI << "Non-active player: " << nonActivePlayer().getName() << '\n';

        for (int i{}; i < STARTING_HAND_SIZE; ++i)
        {
            activePlayer().drawCard(m_deck);
            nonActivePlayer().drawCard(m_deck);
        }
        // TODO: Implement mulligan rules
        DLOGI << "Game constructed\n";

        DLOGI << "Changing phase to beginning phase\n";
        changePhase(std::make_unique<BeginningPhase>((*this)));
    }
#ifdef DANDAN_BUILD_SERIALIZE
    Game::Game()
    {
        GameSetup();
    }
#endif

    Game::Game(Deck &&deck) : m_deck{std::move(deck)}
    {
        DLOGI << "Game constructed with explicit deck\n";
        GameSetup();
    }

    Game::Game(std::istream &input) : m_input{&input}
    {
        GameSetup();
    }

    Game Game::withIstream(std::istream &input)
    {
        return Game{input};
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
            DLOGI << "Passing turn\n";
            m_first_turn = false;
            m_active_player_index =
                (m_active_player_index + 1) % AMOUNT_PLAYERS;
            changePhase(std::make_unique<BeginningPhase>(
                std::reference_wrapper<Game>(*this)));
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
        printCards(getNonActivePlayer().hand().getCards());
        std::cout << "\n";

        // Player's battlefield
        std::cout << getNonActivePlayer().getName() << "'s Battlefield: ";
        printCards(getNonActivePlayer().battlefield().getPermanents());
        std::cout << "\n\n"; // space between battlefields

        // Opponent's battlefield
        std::cout << getActivePlayer().getName() << "'s Battlefield: ";
        printCards(getActivePlayer().battlefield().getPermanents());
        std::cout << "\n";

        // Opponent's hand and name
        std::cout << getActivePlayer().getName() << "'s Hand: ";
        printCards(getActivePlayer().hand().getCards());
        std::cout << "\n";
    }
} // namespace dandan::core