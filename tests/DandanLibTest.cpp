#include "dandan/dandan.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

TEST(DandanLibTest, GameSetup)
{
    dandan::Game game{};
    auto &active_player = game.getActivePlayer();

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