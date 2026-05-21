#include "dandan/abilities/IAbility.h"
#include "dandan/core/PlayerID.h"
#include "dandan/dandan.h"
#include "dandan/mana/GenericMana.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <vector>

#include "common.h"

static constexpr int TEST_DECK_SIZE{20};

TEST(DandanLibTest, GameSetup)
{
    dandan::core::PlayerID::reset();
    auto library{createTestDeck(TEST_DECK_SIZE)};
    auto game{dandan::Game::withLibrary(std::move(library))};

    auto &active_player = game.activePlayer();

    std::vector<std::string> card_names;
    std::transform(
        active_player.hand().getCards().begin(),
        active_player.hand().getCards().end(), std::back_inserter(card_names),
        [&game](const auto &card)
        { return std::string(game.getCardByID(card)->getData().getName()); });

    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        auto card_id = active_player.hand().getCards().front();
        auto *card = game.getCardByID(card_id);
        active_player.playCard(*card);
    }

    std::vector<std::string> battlefield_card_names{};

    auto getCardname = [&game](const auto &card)
    { return std::string(game.getCardByID(card)->getData().getName()); };

    for (const auto &[type, cards] :
         active_player.battlefield().getPermanents())
    {
        std::transform(cards.begin(), cards.end(),
                       std::back_inserter(battlefield_card_names), getCardname);
    }

    EXPECT_EQ(card_names, battlefield_card_names);
}

TEST(DandanLibTest, NoDrawFirstTurn)
{
    dandan::core::PlayerID::reset();
    auto library{createTestDeck(TEST_DECK_SIZE)};
    auto game{dandan::Game::withLibrary(std::move(library))};

    auto &active_player = game.activePlayer();
    auto &non_active_player = game.nonActivePlayer();

    EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE);
    EXPECT_EQ(non_active_player.hand().getCards().size(), STARTING_HAND_SIZE);

    game.handlePhase();
    // Active player should not draw a card on the first turn
    EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE);
    // Non active player should draw a card on the first turn
    game.passTurn();
    game.handlePhase();
    EXPECT_EQ(non_active_player.hand().getCards().size(),
              STARTING_HAND_SIZE + 1);
}

TEST(DandanLibTest, Bounceland)
{
    dandan::core::PlayerID::reset();

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>()};

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::ETBTrigger>(),
        std::make_unique<dandan::BounceLandEffect>()));

    auto data = dandan::core::CardData{
        "Test Card ", std::make_unique<dandan::mana::GenericMana>(0),
        dandan::core::CardData::Type::Land,
        dandan::core::CardData::SubType::Island, std::move(abilities)};

    auto library = createTestDeck(TEST_DECK_SIZE, &data);

    std::istringstream input_stream(
        "play 0\n0\npass\nplay 0\n0\npass\n0\nquit\n");
    dandan::core::Game game{dandan::Game::withLibrary(std::move(library))};
    game.setIstream(input_stream);

    game.run();
}

TEST(DandanLibTest, Play1LandATurnTest)
{

    dandan::core::PlayerID::reset();
    auto library{createTestDeck(TEST_DECK_SIZE)};
    dandan::core::Game game{dandan::Game::withLibrary(std::move(library))};
    std::stringstream input_stream{};
    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        input_stream << "play 0\n";
    }
    input_stream << "quit\n";
    game.setIstream(input_stream);

    game.run();

    // only one land should be played since the second play should be prevented
    EXPECT_EQ(game.activePlayer().battlefield().getLands().size(), 1);
}

TEST(DandanLibTest, DiscardToHandSize)
{
    dandan::core::PlayerID::reset();

    std::istringstream input_stream("pass\npass\n0\nquit\n");
    auto library{createTestDeck(TEST_DECK_SIZE)};
    dandan::core::Game game{dandan::Game::withLibrary(std::move(library))};
    game.setIstream(input_stream);

    game.run();

    // both players should be down to 7 cards in hand after discarding down to
    // hand size at the end of the turn
    EXPECT_EQ(game.activePlayer().hand().getCards().size(), STARTING_HAND_SIZE);
    EXPECT_EQ(game.nonActivePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE);
}