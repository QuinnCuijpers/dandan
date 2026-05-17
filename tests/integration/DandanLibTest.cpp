#include "dandan/abilities/IAbility.h"
#include "dandan/core/PlayerID.h"
#include "dandan/dandan.h"
#include "dandan/mana/GenericMana.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "common.h"

static constexpr int TEST_DECK_SIZE{20};

TEST(DandanLibTest, GameSetup)
{
    dandan::core::PlayerID::reset();
    auto deck{createTestDeck(TEST_DECK_SIZE)};
    auto game{dandan::Game::withDeck(std::move(deck))};

    auto &active_player = game.activePlayer();

    std::vector<std::string> card_names;
    std::transform(active_player.hand().getCards().begin(),
                   active_player.hand().getCards().end(),
                   std::back_inserter(card_names), [](const auto &card)
                   { return std::string(card.getData().getName()); });

    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        active_player.playCard(0);
    }

    std::vector<std::string> battlefield_card_names{};

    std::transform(active_player.battlefield().getPermanents().begin(),
                   active_player.battlefield().getPermanents().end(),
                   std::back_inserter(battlefield_card_names),
                   [](const auto &card)
                   { return std::string(card.getData().getName()); });

    EXPECT_EQ(card_names, battlefield_card_names);
}

TEST(DandanLibTest, NoDrawFirstTurn)
{
    dandan::core::PlayerID::reset();
    auto deck{createTestDeck(TEST_DECK_SIZE)};
    auto game{dandan::Game::withDeck(std::move(deck))};

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
    auto cards = std::vector<dandan::Card>{};
    auto card_data = std::vector<dandan::core::CardData *>{};

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>()};

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::ETBTrigger>(),
        std::make_unique<dandan::BounceLandEffect>()));

    auto data = dandan::core::CardData{
        "Test Card ", std::make_unique<dandan::mana::GenericMana>(0),
        dandan::core::CardData::Type::Land,
        dandan::core::CardData::SubType::Island, std::move(abilities)};

    card_data.reserve(TEST_DECK_SIZE);
    for (int i{}; i < TEST_DECK_SIZE; ++i)
    {
        card_data.push_back(&data);
        cards.emplace_back(card_data.back());
    };

    std::istringstream input_stream("play 0\n0\npass\nplay 0\n0\npass\nquit\n");
    dandan::core::Deck testDeck{cards};
    dandan::core::Game game{dandan::Game::withIstream(input_stream)};
    game.setDeck(std::move(testDeck));

    game.run();
}

TEST(DandanLibTest, Play1LandATurnTest)
{

    dandan::core::PlayerID::reset();
    auto deck{createTestDeck(TEST_DECK_SIZE)};
    dandan::core::Game game{dandan::Game::withDeck(std::move(deck))};
    std::istringstream input_stream("play 0\nplay 0\nquit\n");
    game.setIstream(input_stream);

    game.run();

    // only one land should be played since the second play should be prevented
    EXPECT_EQ(game.activePlayer().battlefield().getPermanents().size(), 1);
}

TEST(DandanLibTest, DiscardToHandSize)
{
    dandan::core::PlayerID::reset();

    std::istringstream input_stream("pass\npass\n0\nquit\n");
    auto deck{createTestDeck(TEST_DECK_SIZE)};
    dandan::core::Game game{dandan::Game::withDeck(std::move(deck))};
    game.setIstream(input_stream);

    game.run();

    // both players should be down to 7 cards in hand after discarding down to
    // hand size at the end of the turn
    EXPECT_EQ(game.activePlayer().hand().getCards().size(), STARTING_HAND_SIZE);
    EXPECT_EQ(game.nonActivePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE);
}

// TODO: impl
//  TEST(DandanLibTest, Mulligan)
//  {
//      // NOLINTBEGIN
//      auto cards = std::vector<dandan::Card>{};
//      for (int i{}; i < TEST_DECK_SIZE; ++i)
//      {
//          auto data = dandan::core::CardData(
//              "Test Card " + std::to_string(i),
//              std::move(std::make_unique<dandan::mana::GenericMana>(i)),
//              dandan::core::CardData::Type::Land,
//              dandan::core::CardData::SubType::Island);
//          cards.push_back(dandan::Card{&data});
//      };

//     // NOLINTEND

//     dandan::core::Deck testDeck{cards};
//     dandan::core::Game game{std::move(testDeck)};

//     auto &active_player = game.activePlayer();

//     EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE);

//     active_player.mulligan();

//     EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE -
//     1);
// }