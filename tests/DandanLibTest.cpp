#include "dandan/abilities/IAbility.h"
#include "dandan/core/PlayerID.h"
#include "dandan/dandan.h"
#include "dandan/mana/GenericMana.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

static constexpr int TEST_DECK_SIZE{20};

static void bounceLandHelper(dandan::core::Game &game, int land_index)
{
    auto land{game.activePlayer().battlefield().getPermanent(land_index)};
    game.activePlayer().hand().addCard(land);
}

TEST(DandanLibTest, GameSetup)
{
    dandan::core::PlayerID::reset();
    // TODO: replace with test fixture
    auto cards = std::vector<dandan::Card>{};
    auto card_data = std::vector<dandan::core::CardData>{};
    card_data.reserve(TEST_DECK_SIZE);
    for (int i{}; i < TEST_DECK_SIZE; ++i)
    {
        auto data = dandan::core::CardData(
            "Test Card " + std::to_string(i),
            std::make_unique<dandan::mana::GenericMana>(i),
            dandan::core::CardData::Type::Land,
            dandan::core::CardData::SubType::Island);
        card_data.push_back(std::move(data));
        cards.emplace_back(&card_data.back());
    };

    dandan::core::Deck testDeck{cards};
    dandan::core::Game game{std::move(testDeck)};

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
    auto cards = std::vector<dandan::Card>{};
    auto card_data = std::vector<dandan::core::CardData>{};
    card_data.reserve(TEST_DECK_SIZE);
    for (int i{}; i < TEST_DECK_SIZE; ++i)
    {
        auto data = dandan::core::CardData(
            "Test Card " + std::to_string(i),
            std::make_unique<dandan::mana::GenericMana>(i),
            dandan::core::CardData::Type::Land,
            dandan::core::CardData::SubType::Island);
        card_data.push_back(std::move(data));
        cards.emplace_back(&card_data.back());
    };

    dandan::core::Deck testDeck{cards};
    dandan::core::Game game{std::move(testDeck)};

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

// this test is a bit of a hack as we manually implement the event system for
// the bounce land effect
TEST(DandanLibTest, Bounceland)
{
    dandan::core::PlayerID::reset();
    auto cards = std::vector<dandan::Card>{};
    auto card_data = std::vector<dandan::core::CardData>{};
    card_data.reserve(TEST_DECK_SIZE);
    for (int i{}; i < TEST_DECK_SIZE; ++i)
    {
        auto abilities{
            std::vector<std::unique_ptr<dandan::abilities::IAbility>>()};

        abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
            std::make_unique<dandan::ETBTrigger>(),
            std::make_unique<dandan::BounceLandEffect>()));

        auto data = dandan::core::CardData{
            "Test Card " + std::to_string(i),
            std::make_unique<dandan::mana::GenericMana>(i),
            dandan::core::CardData::Type::Land,
            dandan::core::CardData::SubType::Island, std::move(abilities)};
        card_data.push_back(std::move(data));
        cards.emplace_back(&card_data.back());
    };

    dandan::core::Deck testDeck{cards};
    dandan::core::Game game{std::move(testDeck)};

    // handle beginning phase
    game.handlePhase();

    // play the land with the bounce effect
    game.activePlayer().playCard(0);
    bounceLandHelper(game, 0);

    // same amount of cards in hand after bounce
    EXPECT_EQ(game.activePlayer().hand().getCards().size(), STARTING_HAND_SIZE);

    game.passTurn();
    game.handlePhase();
    // bounce should trigger on opponent's turn
    game.activePlayer().playCard(0);
    bounceLandHelper(game, 0);
    EXPECT_EQ(game.activePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE + 1);
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