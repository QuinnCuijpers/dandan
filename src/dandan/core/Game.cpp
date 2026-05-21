#include "dandan/core/Game.h"
#include "dandan/conditions/PlayedLandCondition.h"
#include "dandan/conditions/StartingPlayerCondition.h"
#include "dandan/core/Player.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/effects/continuous/prevention/PlayCardPreventionEffect.h"
#include "dandan/log.h"
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

        auto one_land_a_turn{
            std::make_unique<effects::PlayCardPreventionEffect>(
                std::make_unique<conditions::PlayedLandCondition>())};

        m_prevention_manager.subscribe(std::move(no_draw_starting_player));
        m_prevention_manager.subscribe(std::move(one_land_a_turn));

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
#ifdef DANDAN_SERIALIZE
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

    Game Game::withDeck(core::Deck &&deck)
    {
        return Game(std::move(deck));
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
            changePhase(std::make_unique<BeginningPhase>(*this));
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

        // opponents name and hand (top)
        std::cout << nonActivePlayer().getName() << "'s Hand: ";
        printCards(nonActivePlayer().hand().getCards());
        std::cout << "\n";

        // Opponents player's lands
        std::cout << nonActivePlayer().getName() << "'s Lands: ";
        printCards(nonActivePlayer().battlefield().getLands());
        std::cout << "\n";

        // Opponent's battlefield
        std::cout << nonActivePlayer().getName() << "'s Creatures: ";
        printCards(nonActivePlayer().battlefield().getCreatures());
        std::cout << "\n\n"; // space between battlefields

        // Active player's creatures
        std::cout << activePlayer().getName() << "'s Creatures: ";
        printCards(activePlayer().battlefield().getCreatures());
        std::cout << "\n";

        // Active player's lands
        std::cout << activePlayer().getName() << "'s Lands: ";
        printCards(activePlayer().battlefield().getLands());
        std::cout << "\n";

        // Active player's hand and name
        std::cout << activePlayer().getName() << "'s Hand: ";
        printCards(activePlayer().hand().getCards());
        std::cout << "\n";

        std::cout << "Cards in deck: " << m_deck.getCards().size() << "\n";
    }
} // namespace dandan::core