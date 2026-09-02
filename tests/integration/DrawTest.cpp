#include "common/LandDefinitions.h"
#include "common/SpellDefinitions.h"
#include "common/TestCardsCreate.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, BrainstormTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_ISLANDS{6};
    static constexpr int NUM_BRAINSTORMS{14};

    auto island_abilities{Island_TESTS_Abilities()};
    auto brainstorm_abilities{Brainstorm_Abilities()};

    auto island_data{dandan::core::CardData{
        "Island",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::Island},
        dandan::core::SuperType::Basic,
        std::move(island_abilities),
        std::nullopt}};

    auto brainstorm_data{
        dandan::core::CardData{"Brainstorm",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 1}}},
                               dandan::core::Type::Instant,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(brainstorm_abilities),
                               std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto brainstorms{createTestCards(NUM_BRAINSTORMS, &brainstorm_data)};
    cards.insert(cards.end(), brainstorms.begin(), brainstorms.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};

    std::stringstream stream{};

    // index 1
    auto card_1_id{game_state.activePlayer().hand().getCards()[1]};
    // index 2
    auto card_2_id{game_state.activePlayer().hand().getCards()[2]};

    auto island_id{game_state.activePlayer().hand().getCards()[0]};

    stream << "play " << island_id.getID() << '\n'; // play island
    stream << "activate " << island_id.getID()
           << '\n'; // activate island for mana to be
                    // able to cast brainstorm
    stream << "play "
           << game_state.activePlayer()
                  .hand()
                  .getCards()[(NUM_ISLANDS / 2) + 1]
                  .getID()
           << '\n';  // play brainstorm, also checks if cards are drawn in
                     // the correct order
    stream << "0\n"; // choose to put card_1 on top of the library
    stream << "0\n"; // choose to put card_2 on top of the library
    stream << "pass\n";

    // player 2 now draws card_2
    stream << "play " << card_2_id.getID() << '\n';
    stream << "pass\n"; // pass the turn

    // player 1 draws card_1
    stream << "play " << card_1_id.getID() << '\n';
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *card_1{card_registry[card_1_id]};
    auto *card_2{card_registry[card_2_id]};

    EXPECT_EQ(card_1->getZone(), dandan::core::Zone::BATTLEFIELD);
    EXPECT_EQ(card_1->getControllerID(), game_state.activePlayer().getID());

    EXPECT_EQ(card_2->getZone(), dandan::core::Zone::BATTLEFIELD);
    EXPECT_EQ(card_2->getControllerID(), game_state.nonActivePlayer().getID());
}

TEST(DandanLibTest, AccumulatedKnowledgeTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_SVYELUNITE{6};
    static constexpr int NUM_ACCUMULATED{30};

    auto svyenulite_abilities{Svyelunite_Temple_Abilities()};
    auto accumulated_knowledge_abilities{Accumulated_Knowledge_Abilities()};

    auto svyenulite_temple_data{dandan::core::CardData{
        "Svyelunite Temple",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(svyenulite_abilities),
        std::nullopt}};

    auto accumulated_knowledge_data{dandan::core::CardData{
        "Accumulated Knowledge",
        dandan::mana::ManaPrice{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
        dandan::core::Type::Instant,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(accumulated_knowledge_abilities),
        std::nullopt}};

    auto cards{createTestCards(NUM_SVYELUNITE, &svyenulite_temple_data)};
    auto accumulated_knowledge_cards{
        createTestCards(NUM_ACCUMULATED, &accumulated_knowledge_data)};
    cards.insert(cards.end(), accumulated_knowledge_cards.begin(),
                 accumulated_knowledge_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};

    auto &card_registry{game.execution_context().cards.get()};

    std::stringstream stream{};

    auto svyenulite_id_1{game_state.activePlayer().hand().getCards()[0]};
    auto svyenulite_id_2{game_state.nonActivePlayer().hand().getCards()[0]};

    auto accumulated_knowledge_id_1{
        *std::find_if(game_state.activePlayer().hand().getCards().begin(),
                      game_state.activePlayer().hand().getCards().end(),
                      [&card_registry](const auto &card_id)
                      {
                          const auto *card = card_registry[card_id];
                          return card != nullptr && card->getData().name ==
                                                        "Accumulated Knowledge";
                      })};
    auto accumulated_knowledge_id_2{
        *std::find_if(game_state.nonActivePlayer().hand().getCards().begin(),
                      game_state.nonActivePlayer().hand().getCards().end(),
                      [&card_registry](const auto &card_id)
                      {
                          const auto *card = card_registry[card_id];
                          return card != nullptr && card->getData().name ==
                                                        "Accumulated Knowledge";
                      })};

    // turn 1 player 1
    stream << "play " << svyenulite_id_1.getID() << '\n'; // play island
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << svyenulite_id_2.getID() << '\n';
    stream << "pass\n";

    // turn 2 player 1
    stream << "activate " << svyenulite_id_1.getID()
           << '\n';  // activate land for mana
    stream << "1\n"; // option 1
    stream << "play " << accumulated_knowledge_id_1.getID() << '\n';
    stream << "pass\n";

    // turn 2 player 2
    stream << "activate " << svyenulite_id_2.getID()
           << '\n';  // activate land for mana
    stream << "1\n"; // option 1
    stream << "play " << accumulated_knowledge_id_2.getID() << '\n';
    stream << "pass\n";

    // turn 2 player 2
    stream << "pass\n";
    // discard down to hand size
    stream << game_state.nonActivePlayer().hand().getCards()[1].getID() << '\n';
    stream << game_state.nonActivePlayer().hand().getCards()[2].getID() << '\n';

    // Turn 3 player 1
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    EXPECT_EQ(game_state.activePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE + 1);
    EXPECT_EQ(game_state.nonActivePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE);

    auto *svyenulite_1{card_registry[svyenulite_id_1.getID()]};
    auto *svyenulite_2{card_registry[svyenulite_id_2.getID()]};

    EXPECT_EQ(svyenulite_1->getZone(), dandan::core::Zone::GRAVEYARD);
    EXPECT_EQ(svyenulite_2->getZone(), dandan::core::Zone::GRAVEYARD);

    std::cout << accumulated_knowledge_id_1.getID() << '\n';
    std::cout << accumulated_knowledge_id_2.getID() << '\n';
    auto *accumulated_knowledge_1{
        card_registry[accumulated_knowledge_id_1.getID()]};
    auto *accumulated_knowledge_2{
        card_registry[accumulated_knowledge_id_2.getID()]};

    EXPECT_EQ(accumulated_knowledge_1->getZone(),
              dandan::core::Zone::GRAVEYARD);
    EXPECT_EQ(accumulated_knowledge_2->getZone(),
              dandan::core::Zone::GRAVEYARD);
}
