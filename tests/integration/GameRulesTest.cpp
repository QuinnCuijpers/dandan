#include "common/TestCardsCreate.h"
#include "common/common.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, NoDrawFirstTurn)
{
    dandan::core::PlayerID::reset();
    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    auto &active_player = game_state.activePlayer();
    auto &non_active_player = game_state.nonActivePlayer();

    EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE);
    EXPECT_EQ(non_active_player.hand().getCards().size(), STARTING_HAND_SIZE);

    game_state.handlePhase();
    // Active player should not draw a card on the first turn
    EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE);
    // Non active player should draw a card on the first turn
    game_state.passTurn(game.execution_context());
    game_state.handlePhase();
    EXPECT_EQ(non_active_player.hand().getCards().size(),
              STARTING_HAND_SIZE + 1);
}

TEST(DandanLibTest, Play1LandATurnTest)
{

    dandan::core::PlayerID::reset();
    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};
    std::stringstream input_stream{};
    const auto &hand_cards = game_state.activePlayer().hand().getCards();
    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        input_stream << "play " << hand_cards[i].getID() << '\n';
    }
    input_stream << "quit\n";
    game.setIstream(input_stream);

    game.run();

    // only one land should be played since the second play should be prevented
    EXPECT_EQ(game_state.activePlayer().battlefield().getLands().size(), 1);
}

TEST(DandanLibTest, DiscardToHandSize)
{
    dandan::core::PlayerID::reset();

    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    std::stringstream stream{};
    for (size_t i{}; i < dandan::core::AMOUNT_PLAYERS; ++i)
    {
        stream << "pass\n";
    }
    // the non-active player will be the one prompted to discard on cleanup
    stream << game_state.nonActivePlayer().hand().getCards().front().getID()
           << '\n';
    stream << "quit\n";

    game.setIstream(stream);

    game.run();

    EXPECT_EQ(game_state.activePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE + 1);
    EXPECT_EQ(game_state.nonActivePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE);
}

TEST(DandanLibTest, DieFromEmptyLibrary)
{
    dandan::core::PlayerID::reset();

    const int MIN_LIB_SIZE = 14;
    auto test_cards{createTestCards(MIN_LIB_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    std::stringstream stream{};

    // pass until the library is empty and the active player tries to draw from
    // an empty library
    stream << "pass\n"; // first player passes, second player draws for turn and
                        // dies, the game should end before the second player
                        // can input anything

    game.setIstream(stream);
    game.run();

    EXPECT_TRUE(game_state.activePlayer().lost());
}

TEST(DandanLibTest, DieFromNoLife)
{
    dandan::core::PlayerID::reset();

    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};
    dandan::core::ExecutionContext ctx{game.execution_context()};
    game_state.activePlayer().takeDamage(
        game_state.activePlayer().getLifeTotal(), ctx);
    game.run();

    EXPECT_TRUE(game_state.activePlayer().lost());
}

TEST(DandanLibTest, PlayCreatureTest)
{
    dandan::core::PlayerID::reset();

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>()};

    auto data =
        dandan::core::CardData{"Test Card ",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Creature,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(abilities),
                               std::nullopt};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    std::stringstream stream{};
    const auto &hand_cards = game_state.activePlayer().hand().getCards();
    for (size_t i{}; i < STARTING_HAND_SIZE - 1; ++i)
    {
        auto card_id = hand_cards[i];
        stream << "play " << card_id.getID() << '\n';
    }
    stream << "quit\n";
    game.setIstream(stream);

    // beginning phase
    game_state.handlePhase();

    // main phase
    game_state.activePlayer().manaPool().add(dandan::mana::ManaBag{
        {dandan::mana::ManaType::BLUE, 2 * (STARTING_HAND_SIZE - 1)}});

    // should play 6 dandan
    game.run();

    EXPECT_EQ(game_state.activePlayer().battlefield().getCreatures().size(),
              STARTING_HAND_SIZE - 1);
}
