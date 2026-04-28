#include "dandan/dandan.h"
#include "dandan/mana/GenericMana.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

TEST(DandanLibTest, GameSetup)
{
    // NOLINTBEGIN
    auto cards = std::vector<std::unique_ptr<dandan::Card>>{};
    for (int i{}; i < 20; ++i)
    {
        cards.push_back(std::make_unique<dandan::Card>(
            "Test Card " + std::to_string(i),
            std::move(std::make_unique<dandan::mana::GenericMana>(i)),
            dandan::Card::Type::Land, dandan::Card::SubType::Island));
    };

    // NOLINTEND

    dandan::core::Deck testDeck{cards};
    dandan::core::Game game{std::move(testDeck)};

    auto &active_player = game.getActivePlayer();

    game.printCards();

    std::vector<std::string> card_names;
    std::transform(active_player.getHand().getCards().begin(),
                   active_player.getHand().getCards().end(),
                   std::back_inserter(card_names), [](const auto &card)
                   { return std::string(card->getName()); });

    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        active_player.playCard(0);
    }

    std::vector<std::string> battlefield_card_names{};

    std::transform(active_player.getBattlefield().getPermanents().begin(),
                   active_player.getBattlefield().getPermanents().end(),
                   std::back_inserter(battlefield_card_names),
                   [](const auto &card)
                   { return std::string(card->getName()); });

    EXPECT_EQ(card_names, battlefield_card_names);
}