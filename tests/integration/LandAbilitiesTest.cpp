#include "common/LandDefinitions.h"
#include "common/TestCardsCreate.h"
#include "common/common.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, Bounceland)
{
    dandan::core::PlayerID::reset();

    auto abilities{Izzet_Boilerworks_Abilities()};

    auto data = dandan::core::CardData{"Test Card ",
                                       dandan::mana::ManaPrice{},
                                       dandan::core::Type::Land,
                                       {dandan::core::SubType::Island},
                                       dandan::core::SuperType::None,
                                       std::move(abilities),
                                       std::nullopt};

    auto test_cards = createTestCards(TEST_DECK_SIZE, &data);
    std::stringstream stream{};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    // first player
    stream << "play "
           << game_state.activePlayer().hand().getCards().front().getID()
           << "\n";
    stream << "0\n";
    stream << "pass\n";

    // second player

    stream << "play "
           << game_state.nonActivePlayer().hand().getCards().front().getID()
           << '\n';
    stream << "0\n";
    stream << "pass\n";
    stream << game_state.nonActivePlayer().hand().getCards().front().getID()
           << '\n';

    stream << "play "
           << game_state.activePlayer().hand().getCards().front().getID()
           << '\n';
    stream << "0\n";
    stream << "pass\n";
    stream << game_state.activePlayer().hand().getCards().front().getID()
           << '\n';

    stream << "quit\n";

    game.setIstream(stream);

    game.run();

    EXPECT_EQ(game_state.graveyard().getCards().size(), 2);
}

TEST(DandanLibTest, TempleOfEpiphanyTest)
{
    dandan::core::PlayerID::reset();

    auto abilities{Temple_of_Epiphany_Abilities()};

    auto data = dandan::core::CardData{
        "Test Card ",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(abilities),
        std::nullopt};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    std::stringstream stream{};

    auto next_top_card_id{game_state.library().getCards().front()};
    auto next_next_top_card_id{game_state.library().getCards()[1]};

    stream << "play "
           << game_state.activePlayer().hand().getCards().front().getID()
           << '\n';
    stream << "top\n"; // choose to scry to top
    stream << "pass\n";

    stream << "play " << next_top_card_id.getID()
           << '\n'; // play the card that was on top of the library to ensure it
                    // was scryed to the top correctly
    stream << "bottom\n";
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    EXPECT_EQ(game_state.activePlayer().battlefield().getLands().size(), 1);
    EXPECT_EQ(game_state.activePlayer().battlefield().getLands().front(),
              next_top_card_id); // scryed to top

    EXPECT_EQ(game_state.library().getCards().back(),
              next_next_top_card_id); // scryed to bottom
}

TEST(DandanLibTest, HalimarDepthsAbilities)
{
    dandan::core::PlayerID::reset();

    auto abilities{Halimar_Depths_Abilities()};

    auto data = dandan::core::CardData{
        "Test Card ",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(abilities),
        std::nullopt};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    auto game{dandan::Game::withCards(std::move(test_cards))};
    auto &game_state{game.execution_context().state.get()};

    std::stringstream stream{};

    // auto top_1{game_state.library().getCards().front()};
    auto top_2{game_state.library().getCards()[1]};
    auto top_3{game_state.library().getCards()[2]};
    // auto top_4{game_state.library().getCards()[3]};

    stream << "play "
           << game_state.activePlayer().hand().getCards().front().getID()
           << '\n';  // play halimar depths
    stream << "0\n"; // choose to put the first card peeked to the bottom of the
                     // peeked stack
    stream << "0\n"; // choose to put the second card peeked to the bottom of
                     // the peeked stack
    stream << "0\n"; // choose to put the third card peeked to the bottom of the
                     // peeked stack
    stream << "pass\n";

    stream << "play " << top_3.getID()
           << '\n'; // play the card that was on top of the library to ensure it
                    // was peeked to the top correctly
    // keep in the same order
    stream << "2\n";
    stream << "1\n";
    stream << "0\n";
    stream << "pass\n";

    stream << "play " << top_2.getID()
           << '\n'; // play the card that was on top of the library to ensure it
    stream << "0\n";
    stream << "0\n";
    stream << "0\n";

    stream << "quit\n";
    game.setIstream(stream);
    game.run();
}

TEST(DandanLibTest, ActivateCyclingAbilityTest)
{
    dandan::core::PlayerID::reset();

    auto abilities{Remote_Isle_Abilities()};

    auto data =
        dandan::core::CardData{"Test Card ",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 0}}},
                               dandan::core::Type::Land,
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
        stream << "activate " << card_id.getID() << '\n';
    }
    stream << "quit\n";
    game.setIstream(stream);

    // beginning phase
    game_state.handlePhase();

    // main phase
    game_state.activePlayer().manaPool().add(dandan::mana::ManaBag{
        {dandan::mana::ManaType::BLUE, 2 * (STARTING_HAND_SIZE - 1)}});

    // should activate 6 cycling abilities
    game.run();

    auto size = game_state.library().getCards().size();
    std::cout << "Library size: " << size << '\n';
    EXPECT_EQ(size, TEST_DECK_SIZE - (2 * STARTING_HAND_SIZE) -
                        (STARTING_HAND_SIZE - 1));
}
