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
#include <utility>

#ifdef DANDAN_SERIALIZE
#include <fstream>
#endif

namespace dandan::core
{
#ifdef DANDAN_SERIALIZE
    void Game::loadCards(const std::filesystem::path &path)
    {
        std::ifstream file{path};
        while (file)
        {
            std::string line;
            std::getline(file, line);
            if (!line.empty())
            {
                std::stringstream stream{line};
                std::string name;
                int amount{};
                stream >> amount;
                stream.ignore(1, ' '); // Ignore the space after the amount
                std::getline(stream, name);
                std::cout << "Adding " << amount << " copies of " << name
                          << " to the library.\n";
                for (int i = 0; i < amount; ++i)
                {
                    m_cards.emplace_back(name);
                }
            }
        }
    }
#endif

    void Game::GameSetup()
    {
#ifdef DANDAN_SERIALIZE
        loadCards(m_card_data_path);
#endif

        for (auto &card : m_cards)
        {
            m_card_map.emplace(card.getID(), &card);
            m_library.addCard(card);
        }

        m_library.shuffle();

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
            activePlayer().drawCard(m_library, *this);
            nonActivePlayer().drawCard(m_library, *this);
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

    Game::Game(std::vector<Card> cards)
        : m_cards{std::deque<Card>{cards.begin(), cards.end()}}
    {
        DLOGI << "Game constructed with explicit cards\n";
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

    Game Game::withCards(std::vector<Card> cards)
    {
        return Game(std::move(cards));
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

    const Card *Game::getCardByID(CardID card_id) const
    {
        auto iter = m_card_map.find(card_id);
        if (iter == m_card_map.end())
        {
            throw std::runtime_error("Card with ID " +
                                     std::to_string(card_id.getID()) +
                                     " doesn't exist in the game");
        }
        return iter->second;
    }

    const Card *Game::getCardByID(int card_id) const
    {
        return getCardByID(CardID::fromInt(card_id));
    }

    Card *Game::getCardByID(CardID card_id)
    {
        auto iter = m_card_map.find(card_id);
        if (iter == m_card_map.end())
        {
            throw std::runtime_error("Card with ID " +
                                     std::to_string(card_id.getID()) +
                                     " doesn't exist in the game");
        }
        return iter->second;
    }

    Card *Game::getCardByID(int card_id)
    {
        return getCardByID(CardID::fromInt(card_id));
    }

    void Game::moveCardFromZone(const Card &card)
    {
        switch (card.getZone())
        {
        case Zone::HAND:
            activePlayer().hand().removeCard(card);
            break;
        case Zone::LIBRARY:
        case Zone::BATTLEFIELD:
        case Zone::GRAVEYARD:
        case Zone::EXILE:
        case Zone::STACK:
            break;
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

        // opponnet life total and mana pool
        std::cout << nonActivePlayer().getName()
                  << "'s Life Total: " << nonActivePlayer().getLifeTotal()
                  << '\n';
        std::cout << nonActivePlayer().getName() << "'s Mana Pool: ";
        std::cout << nonActivePlayer().manaPool() << "\n";
        std::cout << "\n";

        // opponents hand (top)`
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

        // Active player's hand
        std::cout << activePlayer().getName() << "'s Hand: ";
        printCards(activePlayer().hand().getCards());
        std::cout << "\n";

        // active player life total and mana pool
        std::cout << activePlayer().getName() << "'s Mana Pool: ";
        std::cout << activePlayer().manaPool() << "\n";
        std::cout << activePlayer().getName()
                  << "'s Life Total: " << activePlayer().getLifeTotal() << '\n';
        std::cout << "\n";

        std::cout << "Cards in library: " << m_library.getCards().size()
                  << "\n";
    }
} // namespace dandan::core