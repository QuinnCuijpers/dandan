#include "dandan/dandan.h"
#include <gtest/gtest.h>
#include <unordered_set>

TEST(DandanLibTest, GameSetup)
{
    dandan::Game game{};
    auto &active_player = game.getActivePlayer();

    std::unordered_set<std::string> card_names;
    for (const auto &card : active_player.getHand().getCards())
    {
        card_names.insert(std::string(card->getName()));
    }

    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        active_player.playCard(0);
    }

    for (const auto &card : active_player.getBattlefield().getPermanents())
    {
        EXPECT_TRUE(card_names.find(std::string(card->getName())) !=
                    card_names.end());
    }
}