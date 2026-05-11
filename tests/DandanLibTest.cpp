#include "dandan/dandan.h"
#include "dandan/mana/GenericMana.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

TEST(DandanLibTest, GameSetup)
{
    // TODO: replace with comptime testdeck generation?
    // NOLINTBEGIN
    auto cards = std::vector<dandan::Card>{};
    for (int i{}; i < 20; ++i)
    {
        auto data = dandan::core::CardData(
            "Test Card " + std::to_string(i),
            std::move(std::make_unique<dandan::mana::GenericMana>(i)),
            dandan::core::CardData::Type::Land,
            dandan::core::CardData::SubType::Island);
        cards.push_back(dandan::Card{&data});
    };

    // NOLINTEND

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
    // NOLINTBEGIN
    auto cards = std::vector<dandan::Card>{};
    for (int i{}; i < 20; ++i)
    {
        auto data = dandan::core::CardData(
            "Test Card " + std::to_string(i),
            std::move(std::make_unique<dandan::mana::GenericMana>(i)),
            dandan::core::CardData::Type::Land,
            dandan::core::CardData::SubType::Island);
        cards.push_back(dandan::Card{&data});
    };

    // NOLINTEND

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

// TODO: impl
//  TEST(DandanLibTest, Bounceland)

// TODO: impl
//  TEST(DandanLibTest, Mulligan)
//  {
//      // NOLINTBEGIN
//      auto cards = std::vector<dandan::Card>{};
//      for (int i{}; i < 20; ++i)
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