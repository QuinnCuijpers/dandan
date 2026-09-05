#include "common/TestCardsCreate.h"
#include "common/common.h"
#include "dandan/dandan.h"
#include <algorithm>
#include <gtest/gtest.h>

TEST(DandanLibTest, gameSetup)
{
    dandan::core::PlayerID::reset();
    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    auto &card_registry{game.execution_context().cards.get()};

    auto &active_player = game_state.activePlayer();

    std::vector<std::string> card_names;
    std::transform(
        active_player.hand().getCards().begin(),
        active_player.hand().getCards().end(), std::back_inserter(card_names),
        [&card_registry](const auto &card)
        { return std::string(card_registry[card]->getData().name); });

    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        auto card_id = active_player.hand().getCards().front();
        auto *card = card_registry[card_id];
        active_player.playCard(*card);
    }

    std::vector<std::string> battlefield_card_names{};

    auto getCardname = [&card_registry](const auto &card)
    { return std::string(card_registry[card]->getData().name); };

    for (const auto &[type, cards] : active_player.battlefield().permanents())
    {
        std::transform(cards.begin(), cards.end(),
                       std::back_inserter(battlefield_card_names), getCardname);
    }

    EXPECT_EQ(card_names, battlefield_card_names);
}

#ifdef DANDAN_SERIALIZE
TEST(DandanLibTest, startGameFromFile)
{
    dandan::core::PlayerID::reset();
    auto input = std::stringstream{};
    input << "quit\n";

    auto game = dandan::Game{dandan::core::DANDAN_DECKLIST};
    game.setIstream(input);
    game.run();
}
#endif
