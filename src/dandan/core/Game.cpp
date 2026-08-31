#include "dandan/core/Game.h"
#include "dandan/conditions/PlayedLandCondition.h"
#include "dandan/conditions/StartingPlayerCondition.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Player.h"
#include "dandan/core/Target.h"
#include "dandan/core/engine/PreventionManager.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/effects/continuous/prevention/PlayCardPreventionEffect.h"
#include "dandan/utils/log.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace dandan::core
{

    void Game::GameSetup(bool shuffle)
    {
        for (auto card_id : m_card_registry.card_ids())
        {
            auto *card = m_card_registry[card_id];
            std::cout << "adding Card id: " << card->getID() << '\n';
            m_game_state.library().addCardBottom(*card);
        }

        if (shuffle)
        {
            m_game_state.library().shuffle();
        }

        auto one_land_a_turn{
            std::make_unique<effects::PlayCardPreventionEffect>(
                std::make_unique<conditions::PlayedLandCondition>())};

        auto no_draw_starting_player{
            std::make_unique<effects::DrawPreventionEffect>(
                std::make_unique<conditions::StartingPlayerCondition>())};

        m_prevention_manager.subscribe(m_game_state.activePlayer().getID(),
                                       std::move(no_draw_starting_player));
        m_prevention_manager.subscribe(std::move(one_land_a_turn));

        DLOGI << "Active player: " << m_game_state.activePlayer().getName()
              << '\n';
        DLOGI << "Non-active player: "
              << m_game_state.nonActivePlayer().getName() << '\n';

        for (int i{}; i < STARTING_HAND_SIZE; ++i)
        {
            m_game_state.activePlayer().drawCard(execution_context());
            m_game_state.nonActivePlayer().drawCard(execution_context());
        }
        // TODO: Implement mulligan rules
        DLOGI << "Game constructed\n";

        DLOGI << "Changing phase to beginning phase\n";
        m_game_state.changePhase(
            std::make_unique<BeginningPhase>((execution_context())));
    }
#ifdef DANDAN_SERIALIZE
    Game::Game(const std::filesystem::path &path)
        : m_priority_manager(m_game_state.activePlayerID())
    {
        m_card_registry.load_cards(path);
        GameSetup();
    }
#endif

    Game::Game(std::vector<Card> cards, bool shuffle)
        : m_priority_manager(m_game_state.activePlayerID())
    {
        auto moved_cards{std::move(cards)};
        m_card_registry.setCards(moved_cards);
        std::cout << "Game constructed with explicit cards\n";
        GameSetup(shuffle);
    }

    Game::Game(std::istream &input, bool shuffle)
        : m_priority_manager(m_game_state.activePlayerID()), m_input{&input}
    {
        GameSetup(shuffle);
    }

    Game Game::withCards(std::vector<Card> cards, bool shuffle)
    {
        return Game(std::move(cards), shuffle);
    }

    void Game::run()
    {
        try
        {
            while (true)
            {
                while (m_game_state.phase() != nullptr)
                {
                    m_game_state.render(execution_context().cards);
                    m_game_state.handlePhase();
                }
                DLOGI << "Passing turn\n";
                m_game_state.passTurn(execution_context());
            }
        }
        catch (const std::runtime_error &e)
        {
            if (std::string(e.what()) == "Game quit by user")
            {
                DLOGI << "Game quit by user\n";
                return;
            }
            std::cout << "Game ended: " << e.what() << '\n';
        }
    }

} // namespace dandan::core
