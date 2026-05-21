#ifndef DANDAN_GAME_H
#define DANDAN_GAME_H

#include "EventManager.h"
#include "Player.h"
#include "ReplacementManager.h"
#include "Stack.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Constants.h"
#include "dandan/core/Library.h"
#include "dandan/core/PreventionManager.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include "dandan/core/phases/IPhase.h"
#include <filesystem>
#include <istream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace dandan::core
{
    // TODO: implement builder pattern to make it easier to build
    // OR make the game setup be a function that needs to be called explicitly
    class Game
    {
    public:
#ifdef DANDAN_SERIALIZE
        Game();
#endif

        static Game withIstream(std::istream &input);
        static Game withCards(std::vector<Card> cards);

        [[nodiscard]] const Player &activePlayer() const
        {
            return m_players.at(m_active_player_index);
        }

        [[nodiscard]] Player &activePlayer()
        {
            return m_players.at(m_active_player_index);
        }

        [[nodiscard]] const Player &nonActivePlayer() const
        {
            return m_players.at(1 - m_active_player_index);
        }

        [[nodiscard]] Player &nonActivePlayer()
        {
            return m_players.at(1 - m_active_player_index);
        }

        [[nodiscard]] Library &library()
        {
            return m_library;
        }

        [[nodiscard]] Stack &stack()
        {
            return m_stack;
        }

        [[nodiscard]] EventManager &eventManager()
        {
            return m_event_manager;
        }

        [[nodiscard]] const EventManager &eventManager() const
        {
            return m_event_manager;
        }

        [[nodiscard]] ReplacementManager &replacementManager()
        {
            return m_replacement_manager;
        }

        [[nodiscard]] const ReplacementManager &replacementManager() const
        {
            return m_replacement_manager;
        }

        [[nodiscard]] std::istream &istream()
        {
            return *m_input;
        }

        void setIstream(std::istream &istream)
        {
            m_input = &istream;
        }

        void changePhase(std::unique_ptr<IPhase> &&phase)
        {
            m_phase = std::move(phase);
        }

        void setLibrary(Library &&library)
        {
            m_library = std::move(library);
        }

        [[nodiscard]] bool isFirstTurn() const
        {
            return m_first_turn;
        }

        void run();

        void printCards(const std::vector<CardID> &card_ids) const
        {
            std::cout << "[";
            for (const auto &card_id : card_ids)
            {
                const auto *card = getCardByID(card_id);
                if (card != nullptr)
                {
                    std::cout << card->getData().getName() << "("
                              << card->getID().getID() << ", "
                              << card->getZone() << "), ";
                }
            }
            std::cout << "]\n";
        }

        void render() const;

        // TODO: this is a temporary solution, should be replaced with proper
        // turn structure and phase handling
        void passTurn()
        {
            changePhase(std::make_unique<EndingPhase>(*this));
            m_active_player_index = 1 - m_active_player_index;
            m_first_turn = false;
            changePhase(std::make_unique<BeginningPhase>(*this));
        }

        void handlePhase()
        {
            assert(m_phase &&
                   "Phase should never be null during handlePhase()");
            auto next_phase = m_phase->handle();
            m_phase = std::move(next_phase);
        }

        [[nodiscard]] bool isActionPrevented(const IAction &action) const
        {
            return m_prevention_manager.isPrevented(action, *this);
        }

        [[nodiscard]] const Card *getCardByID(CardID card_id) const;
        [[nodiscard]] const Card *getCardByID(int card_id) const;
        [[nodiscard]] Card *getCardByID(CardID card_id);
        [[nodiscard]] Card *getCardByID(int card_id);

        void moveCardFromZone(const Card &card);

    private:
        std::array<Player, AMOUNT_PLAYERS> m_players{
            Player(DEFAULT_NAMES.at(0)), Player(DEFAULT_NAMES.at(1))};
        int m_active_player_index{};
        Library m_library;
        Stack m_stack;
        EventManager m_event_manager;
        PreventionManager m_prevention_manager;
        ReplacementManager m_replacement_manager;
        std::unique_ptr<IPhase> m_phase;
        std::istream *m_input{&std::cin};
        // stable container for all cards in the game
        std::deque<Card> m_cards;
        // map from card ID to pointer to card in m_cards for O(1) access to
        // cards by ID
        std::unordered_map<CardID, Card *> m_card_map;
        std::filesystem::path m_card_data_path{DANDAN_DECKLIST};
        bool m_first_turn{true};
        // PlayerID m_priority_player_id{PlayerID::getInvalidID()};
        // Graveyard m_graveyard;

        explicit Game(std::istream &input);
        explicit Game(std::vector<Card> cards);

        void GameSetup();

        void loadCards(const std::filesystem::path &path);

        static void clearScreen();
    };
} // namespace dandan::core

#endif // DANDAN_GAME_H