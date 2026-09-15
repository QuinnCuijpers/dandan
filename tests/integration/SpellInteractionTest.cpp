#include "common/CreatureDefinitions.h"
#include "common/LandDefinitions.h"
#include "common/SpellDefinitions.h"
#include "common/TestCardsCreate.h"
#include "common/common.h"
#include "dandan/core/CardTypes.h"
#include "dandan/dandan.h"
#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaPrice.h"
#include "dandan/mana/ManaType.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, DiminishingReturnsTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_SVYELUNITE{6};
    static constexpr int NUM_DIMINISHING{35};

    static constexpr int DESIRED_HAND_1{4};
    static constexpr int DESIRED_HAND_2{6};

    auto svyenulite_abilities{Svyelunite_Temple_Abilities()};
    auto diminishing_returns_abilities{Diminishing_Returns_Abilities()};

    auto svyenulite_temple_data{dandan::core::CardData{
        "Svyelunite Temple",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(svyenulite_abilities),
        std::nullopt}};

    auto diminishing_returns_data{dandan::core::CardData{
        "Diminishing Returns",
        dandan::mana::ManaPrice{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 2}}, 2},
        dandan::core::Type::Sorcery,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(diminishing_returns_abilities),
        std::nullopt}};

    auto cards{createTestCards(NUM_SVYELUNITE, &svyenulite_temple_data)};
    auto diminishing_returns_cards{
        createTestCards(NUM_DIMINISHING, &diminishing_returns_data)};
    cards.insert(cards.end(), diminishing_returns_cards.begin(),
                 diminishing_returns_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};

    auto &card_registry{game.execution_context().cards.get()};

    std::stringstream stream{};

    auto svyenulite_id_1{game_state.activePlayer().hand().getCards()[0]};
    auto svyenulite_id_2{game_state.activePlayer().hand().getCards()[1]};

    auto discard_1{game_state.nonActivePlayer().hand().getCards()[0]};
    auto discard_2{game_state.nonActivePlayer().hand().getCards()[1]};

    auto diminishing_returns_id_it{
        std::find_if(game_state.activePlayer().hand().getCards().begin(),
                     game_state.activePlayer().hand().getCards().end(),
                     [&card_registry](const auto &card_id)
                     {
                         const auto *card = card_registry[card_id];
                         return card != nullptr &&
                                card->getData().name == "Diminishing Returns";
                     })};

    ASSERT_NE(diminishing_returns_id_it,
              game_state.activePlayer().hand().getCards().end());

    auto diminishing_returns_id{*diminishing_returns_id_it};

    // turn 1 player 1
    stream << "play " << svyenulite_id_1.getID() << '\n'; // play land
    stream << "pass\n";

    // turn 1 player 2
    stream << "pass\n";
    stream << discard_1.getID() << '\n'; // pass and discard

    // turn 1 player 2
    stream << "play " << svyenulite_id_2.getID() << '\n'; // play land
    stream << "pass\n";

    // turn 2 player 2
    stream << "pass\n";
    stream << discard_2.getID() << '\n'; // pass and discard

    // Turn 3 player 1
    stream << "activate " << svyenulite_id_1.getID() << '\n';
    stream << "1\n"; // option 1
    stream << "activate " << svyenulite_id_2.getID() << '\n';
    stream << "1\n"; // option 1
    stream << "play " << diminishing_returns_id.getID() << '\n';
    stream << DESIRED_HAND_1 << '\n'; // choose to draw for player 1
    stream << DESIRED_HAND_2 << '\n'; // choose to draw for player 2
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *svyenulite_1{card_registry[svyenulite_id_1.getID()]};
    auto *svyenulite_2{card_registry[svyenulite_id_2.getID()]};
    auto *discard_card_1{card_registry[discard_1.getID()]};
    auto *discard_card_2{card_registry[discard_2.getID()]};
    auto *diminishing_returns_card{
        card_registry[diminishing_returns_id.getID()]};

    EXPECT_FALSE(svyenulite_1->getZone() == dandan::core::Zone::BATTLEFIELD ||
                 svyenulite_1->getZone() == dandan::core::Zone::GRAVEYARD);
    EXPECT_FALSE(svyenulite_2->getZone() == dandan::core::Zone::BATTLEFIELD ||
                 svyenulite_2->getZone() == dandan::core::Zone::GRAVEYARD);
    EXPECT_FALSE(discard_card_1->getZone() == dandan::core::Zone::GRAVEYARD);
    EXPECT_FALSE(discard_card_2->getZone() == dandan::core::Zone::GRAVEYARD);

    EXPECT_TRUE(diminishing_returns_card->getZone() ==
                dandan::core::Zone::GRAVEYARD);

    EXPECT_EQ(game_state.exile().getCards().size(), 10);

    EXPECT_EQ(game_state.activePlayer().hand().getCards().size(),
              DESIRED_HAND_1);
    EXPECT_EQ(game_state.nonActivePlayer().hand().getCards().size(),
              DESIRED_HAND_2);
}

TEST(DandanLibTest, UnsubstantiateSpellTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_DANDANS{4};
    static constexpr int NUM_ISLANDS{4};
    static constexpr int NUM_UNSUBSTANTIATE{30};

    auto dandan_abilities{::Dandan_Abilities()};
    auto island_abilities{::Island_TESTS_Abilities()};
    auto unsub_abilities{::Unsubstantiate_Abilities()};

    auto island_data{dandan::core::CardData{
        "Island",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::Island},
        dandan::core::SuperType::Basic,
        std::move(island_abilities),
        std::nullopt}};

    auto dandan_data{
        dandan::core::CardData{"Dandan",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Creature,
                               {dandan::core::SubType::Fish},
                               dandan::core::SuperType::None,
                               std::move(dandan_abilities),
                               std::nullopt}};

    auto unsub_data{dandan::core::CardData{
        "Unsubstantiate",
        dandan::mana::ManaPrice{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
        dandan::core::Type::Instant,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(unsub_abilities),
        std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto dandan_cards{createTestCards(NUM_DANDANS, &dandan_data)};
    auto unsub_cards{createTestCards(NUM_UNSUBSTANTIATE, &unsub_data)};

    cards.insert(cards.end(), dandan_cards.begin(), dandan_cards.end());
    cards.insert(cards.end(), unsub_cards.begin(), unsub_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};

    std::stringstream stream{};

    auto island_1_1{game_state.activePlayer().hand().getCards()[0].getID()};
    auto island_1_2{game_state.activePlayer().hand().getCards()[1].getID()};

    auto island_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};
    auto island_2_2{game_state.nonActivePlayer().hand().getCards()[1].getID()};

    auto dandan_2{game_state.nonActivePlayer().hand().getCards()[2].getID()};
    auto unsub_1{game_state.activePlayer().hand().getCards()[4].getID()};

    // turn 1 player 1
    stream << "play " << island_1_1 << '\n';
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << island_2_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 1
    stream << "play " << island_1_2 << '\n';
    stream << "pass\n";

    // turn 2 player 2
    stream << "play " << island_2_2 << '\n';
    stream << "activate " << island_2_2 << '\n';
    stream << "activate " << island_2_1 << '\n';
    stream << "play " << dandan_2 << '\n';

    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << unsub_1 << '\n';
    stream << 0 << '\n'; // only one target for unsubstantiate
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *dandan{card_registry[dandan_2]};
    auto *unsub{card_registry[unsub_1]};
    auto back_card_id{game_state.activePlayer().hand().getCards().back()};

    EXPECT_EQ(dandan->getZone(), dandan::core::Zone::HAND);
    EXPECT_EQ(back_card_id, dandan->getID());

    EXPECT_EQ(unsub->getZone(), dandan::core::Zone::GRAVEYARD);
}

TEST(DandanLibTest, MemoryLapseTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_DANDANS{4};
    static constexpr int NUM_ISLANDS{4};
    static constexpr int NUM_MEMORY_LAPSE{30};

    auto dandan_abilities{::Dandan_Abilities()};
    auto island_abilities{::Island_TESTS_Abilities()};
    auto memory_abilities{::Memory_Lapse_Abilities()};

    auto island_data{dandan::core::CardData{
        "Island",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::Island},
        dandan::core::SuperType::Basic,
        std::move(island_abilities),
        std::nullopt}};

    auto dandan_data{
        dandan::core::CardData{"Dandan",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Creature,
                               {dandan::core::SubType::Fish},
                               dandan::core::SuperType::None,
                               std::move(dandan_abilities),
                               std::nullopt}};

    auto memory_data{dandan::core::CardData{
        "Memory Lapse",
        dandan::mana::ManaPrice{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
        dandan::core::Type::Instant,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(memory_abilities),
        std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto dandan_cards{createTestCards(NUM_DANDANS, &dandan_data)};
    auto memory_cards{createTestCards(NUM_MEMORY_LAPSE, &memory_data)};

    cards.insert(cards.end(), dandan_cards.begin(), dandan_cards.end());
    cards.insert(cards.end(), memory_cards.begin(), memory_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};
    std::stringstream stream{};

    auto island_1_1{game_state.activePlayer().hand().getCards()[0].getID()};
    auto island_1_2{game_state.activePlayer().hand().getCards()[1].getID()};

    auto island_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};
    auto island_2_2{game_state.nonActivePlayer().hand().getCards()[1].getID()};

    auto dandan_2{game_state.nonActivePlayer().hand().getCards()[2].getID()};
    auto memory_1{game_state.activePlayer().hand().getCards()[4].getID()};

    // turn 1 player 1
    stream << "play " << island_1_1 << '\n';
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << island_2_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 1
    stream << "play " << island_1_2 << '\n';
    stream << "pass\n";

    // turn 2 player 2
    stream << "play " << island_2_2 << '\n';
    stream << "activate " << island_2_2 << '\n';
    stream << "activate " << island_2_1 << '\n';
    stream << "play " << dandan_2 << '\n';

    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << memory_1 << '\n';
    stream << 0 << '\n'; // only one target for memory lapse
    stream << "pass\n";  // pass turn to player 1

    // turn 3 player 1
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *dandan{card_registry[dandan_2]};
    auto *memory{card_registry[memory_1]};
    auto back_card_id{game_state.activePlayer().hand().getCards().back()};

    EXPECT_EQ(dandan->getZone(), dandan::core::Zone::HAND);
    EXPECT_EQ(back_card_id, dandan->getID());

    EXPECT_EQ(memory->getZone(), dandan::core::Zone::GRAVEYARD);
}

TEST(DandanLibTest, DandanCrystalSprayTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_ISLANDS{6};
    static constexpr int NUM_CRYSTAL{30};

    auto island_abilities{::Island_TESTS_Abilities()};
    auto crystal_abilities{::Crystal_Spray_Abilities()};

    auto island_data{dandan::core::CardData{
        "Island",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::Island},
        dandan::core::SuperType::Basic,
        std::move(island_abilities),
        std::nullopt}};

    auto crystal_data{dandan::core::CardData{
        "Crystal Spray",
        dandan::mana::ManaPrice{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 2},
        dandan::core::Type::Instant,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(crystal_abilities),
        std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto crystal_cards{createTestCards(NUM_CRYSTAL, &crystal_data)};

    cards.insert(cards.end(), crystal_cards.begin(), crystal_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};
    std::stringstream stream{};

    auto island_1_1{game_state.activePlayer().hand().getCards()[0].getID()};
    auto island_1_2{game_state.activePlayer().hand().getCards()[1].getID()};
    auto island_1_3{game_state.activePlayer().hand().getCards()[2].getID()};

    auto island_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};
    auto island_2_2{game_state.nonActivePlayer().hand().getCards()[1].getID()};

    auto crystal_1_1{game_state.activePlayer().hand().getCards()[4].getID()};

    // turn 1 player 1
    stream << "play " << island_1_1 << '\n';
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << island_2_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 1
    stream << "play " << island_1_2 << '\n';
    stream << "pass\n";

    // turn 2 player 2
    stream << "play " << island_2_2 << '\n';
    stream << "pass\n";

    // turn 3 player 1
    stream << "play " << island_1_3 << '\n';
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "activate " << island_1_3 << '\n';
    stream << "play " << crystal_1_1 << '\n';

    stream << "0\n"; // target land
    stream << "island\n";
    stream << "mountain\n";
    stream << "pass\n";

    // turn 3 player 2
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *crystal{card_registry[crystal_1_1]};
    EXPECT_EQ(crystal->getZone(), dandan::core::Zone::GRAVEYARD);

    for (auto &player : game_state.getPlayers())
    {
        for (auto card : player.battlefield().getLands())
        {
            auto *cardp{card_registry[card]};
            EXPECT_EQ(cardp->getCurrentSubTypes(),
                      std::vector{dandan::core::SubType::Island});
        }
    }
}

TEST(DandanLibTest, MysticRetrievalTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_ISLANDS{8};
    static constexpr int NUM_MYSTIC_RETRIEVAL{30};

    auto island_abilities{::Island_TESTS_Abilities()};
    auto mystic_retrieval_abilities{::Mystic_Retrieval_Abilities()};
    auto shivan_abilities{::Shivan_Reef_Abilities()};

    auto shivan_data{
        create_land_data("Shivan Reef", dandan::core::SuperType::None,
                         dandan::core::SubType::None, Shivan_Reef_Abilities())};

    auto mystic_retrieval_data{dandan::core::CardData{
        "Mystic Retrieval",
        dandan::mana::ManaPrice{
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 3},
        dandan::core::Type::Sorcery,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(mystic_retrieval_abilities),
        std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, shivan_data.get())};
    auto mystic_retrieval_cards{
        createTestCards(NUM_MYSTIC_RETRIEVAL, &mystic_retrieval_data),
    };

    cards.insert(cards.end(), mystic_retrieval_cards.begin(),
                 mystic_retrieval_cards.end());

    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};

    std::stringstream stream{};

    auto land_1_1{game_state.activePlayer().hand().getCards()[0].getID()};
    auto land_1_2{game_state.activePlayer().hand().getCards()[1].getID()};
    auto land_1_3{game_state.activePlayer().hand().getCards()[2].getID()};
    auto land_1_4{game_state.activePlayer().hand().getCards()[3].getID()};

    auto land_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};
    auto land_2_2{game_state.nonActivePlayer().hand().getCards()[1].getID()};
    auto land_2_3{game_state.nonActivePlayer().hand().getCards()[2].getID()};

    auto mystic_1{game_state.activePlayer().hand().getCards()[5].getID()};

    auto mystic_2{game_state.nonActivePlayer().hand().getCards()[5].getID()};
    auto mystic_3{game_state.nonActivePlayer().hand().getCards()[6].getID()};

    // Turn 1 player 1
    stream << "play " << land_1_1 << '\n';
    stream << "pass\n";

    // Turn 1 player 2
    stream << "play " << land_2_1 << '\n';
    stream << "pass\n";

    // Turn 2 player 1
    stream << "play " << land_1_2 << '\n';
    stream << "pass\n";

    // Turn 2 player 2
    stream << "play " << land_2_2 << '\n';
    stream << "pass\n";

    // Turn 3 player 1
    stream << "play " << land_1_3 << '\n';
    stream << "pass\n";

    // Turn 3 player 2
    stream << "play " << land_2_3 << '\n';
    stream << "pass\n";

    // Turn 4 player 1
    stream << "play " << land_1_4 << '\n';
    stream << "pass\n";

    // Turn 4 player 2
    stream << "pass\n";
    stream << mystic_2 << '\n'; // discard the mystic retrival

    // turn 5 player 1
    stream << "pass\n";
    // stream << game_state.activePlayer().hand().getCards().back().getID()
    //        << '\n';

    // turn 5 player 2
    stream << "pass\n";
    stream << mystic_3 << '\n';

    // Turn 6 player 1

    // Cast Mystic Retrieval #1 and target the other copy
    // of Mystic Retrieval in the graveyard.
    stream << "activate " << land_1_1 << '\n';
    stream << "0\n";
    stream << "activate " << land_1_2 << '\n';
    stream << "0\n";
    stream << "activate " << land_1_3 << '\n';
    stream << "0\n";
    stream << "activate " << land_1_4 << '\n';
    stream << "1\n";

    stream << "play " << mystic_1 << '\n';
    stream << mystic_2 << '\n'; // target Mystic Retrieval #2

    // Pass the turn so the opponent gets priority on their next turn.
    stream << "pass\n";
    // discard mystic 2 again
    stream << mystic_2 << '\n';

    // Turn 6 player 2
    //
    // The Mystic Retrieval should now be available
    // to the opponent through flashback.
    stream << "activate " << land_2_1 << '\n';
    stream << "0\n";
    stream << "activate " << land_2_2 << '\n';
    stream << "0\n";
    stream << "activate " << land_2_3 << '\n';
    stream << "2\n";

    stream << "play " << mystic_1 << " flashback\n";
    stream << mystic_3 << '\n';

    stream << "quit\n";

    game.setIstream(stream);

    game.run();

    auto *mystic_1_card{card_registry[mystic_1]};
    auto *mystic_2_card{card_registry[mystic_2]};
    auto *mystic_3_card{card_registry[mystic_3]};

    EXPECT_EQ(mystic_1_card->getZone(), dandan::core::Zone::EXILE);

    EXPECT_EQ(mystic_2_card->getZone(), dandan::core::Zone::GRAVEYARD);

    EXPECT_EQ(mystic_3_card->getZone(), dandan::core::Zone::HAND);
}
