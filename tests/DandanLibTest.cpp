#include "dandan/dandan.h"
#include <gtest/gtest.h>
#include <vector>

TEST(DandanLibTest, GameSetup)
{
    dandan::Game game{};
    auto &active_player = game.getActivePlayer();

    std::vector<std::string> card_names;
    for (const auto &card : active_player.getHand().getCards())
    {
        card_names.emplace_back(card->getName());
    }

    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        active_player.playCard(0);
    }

    std::vector<std::string> battlefield_card_names{};
    for (const auto &card :
         game.getActivePlayer().getBattlefield().getPermanents())
    {
        battlefield_card_names.emplace_back(card->getName());
    }

    EXPECT_EQ(card_names, battlefield_card_names);
}