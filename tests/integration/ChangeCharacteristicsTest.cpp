#include "common/CreatureDefinitions.h"
#include "common/LandDefinitions.h"
#include "common/SpellDefinitions.h"
#include "common/TestCardsCreate.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, DandanMindBendTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_DANDANS{4};
    static constexpr int NUM_ISLANDS{4};
    static constexpr int NUM_MINDBEND{30};

    auto dandan_abilities{::Dandan_Abilities()};
    auto island_abilities{::Island_TESTS_Abilities()};
    auto mind_bend_abilities{::Mind_Bend_Abilities()};

    auto island_data{dandan::core::CardData{
        "Svyelunite Temple",
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

    auto mind_bend_data{
        dandan::core::CardData{"Mind Bend",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 1}}},
                               dandan::core::Type::Instant,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(mind_bend_abilities),
                               std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto dandan_cards{createTestCards(NUM_DANDANS, &dandan_data)};
    auto mind_bend_cards{createTestCards(NUM_MINDBEND, &mind_bend_data)};

    cards.insert(cards.end(), dandan_cards.begin(), dandan_cards.end());
    cards.insert(cards.end(), mind_bend_cards.begin(), mind_bend_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};
    std::stringstream stream{};

    auto island_1_1{game_state.activePlayer().hand().getCards()[0].getID()};

    auto island_1_2{game_state.activePlayer().hand().getCards()[1].getID()};

    auto island_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};

    auto dandan_1_1{game_state.activePlayer().hand().getCards()[2].getID()};
    auto mind_bend_2_1{
        game_state.nonActivePlayer().hand().getCards()[4].getID()};

    // turn 1 player 1
    stream << "play " << island_1_1 << '\n';
    stream << "activate " << island_1_1 << '\n'; // avoids priotity requests
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << island_2_1 << '\n';
    // stream << "activate " << island_2_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 1
    stream << "play " << island_1_2 << '\n';
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << dandan_1_1 << '\n';
    stream << "pass\n"; // pass prio on dandan entering
    stream << "next\n"; // pass priority through phase change to player 2

    stream << "activate " << island_2_1 << '\n';
    stream << "play " << mind_bend_2_1 << '\n';
    stream << 2 << '\n'; // index of dandan in choice list
    stream << "island\n";
    stream << "plains\n";
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *dandan{card_registry[dandan_1_1]};
    EXPECT_EQ(dandan->getZone(), dandan::core::Zone::GRAVEYARD);
}

TEST(DandanLibTest, DanceOfTheSkywiseChangeTest)
{
    dandan::core::PlayerID::reset();

    // global: one land a turn
    // player: no draw on first turn
    // card: summoning sickness per card (3 islands and a dandan)
    static constexpr int EXPECTED_NUM_PREVENTIONS{1 + 1 + 4};

    static constexpr int NUM_DANDANS{4};
    static constexpr int NUM_ISLANDS{4};
    static constexpr int NUM_DANCE{30};

    auto dandan_abilities{Dandan_Abilities()};
    auto island_abilities{::Island_TESTS_Abilities()};
    auto dance_abilities{::Dance_of_the_Skywise_Abilities()};

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

    auto mind_bend_data{
        dandan::core::CardData{"Dance of the Skywise",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Instant,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(dance_abilities),
                               std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto dandan_cards{createTestCards(NUM_DANDANS, &dandan_data)};
    auto dance_cards{createTestCards(NUM_DANCE, &mind_bend_data)};

    cards.insert(cards.end(), dandan_cards.begin(), dandan_cards.end());
    cards.insert(cards.end(), dance_cards.begin(), dance_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};
    auto &replacement_manager{
        game.execution_context().replacement_manager.get()};
    auto &condition_manager{game.execution_context().condition_manager.get()};
    auto &event_manager{game.execution_context().event_manager.get()};
    auto &prevention_manager{game.execution_context().prevention_manager.get()};

    std::stringstream stream{};

    auto island_1_1{game_state.activePlayer().hand().getCards()[0].getID()};

    auto island_1_2{game_state.activePlayer().hand().getCards()[1].getID()};

    auto island_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};

    auto dandan_1_1{game_state.activePlayer().hand().getCards()[2].getID()};
    auto dance_1_1{game_state.activePlayer().hand().getCards()[4].getID()};

    auto discard_2_1{
        game_state.nonActivePlayer().hand().getCards().back().getID()};

    // turn 1 player 1
    stream << "play " << island_1_1 << '\n';
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << island_2_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 1
    stream << "play " << island_1_2 << '\n';
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << dandan_1_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 2
    stream << "pass\n";
    stream << discard_2_1 << '\n';

    // turn 3 player 1
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << dance_1_1 << '\n';
    stream << "0\n";    // choose dandan as target
    stream << "quit\n"; // quit immediately such that dance of the skywise
                        // is still applied

    game.setIstream(stream);
    game.run();

    auto *dandan{card_registry[dandan_1_1]};
    auto expected_subtypes{std::vector{dandan::core::SubType::Dragon,
                                       dandan::core::SubType::Illusion}};

    EXPECT_EQ(dandan->getColor(), dandan::core::ColorWord::Blue);
    EXPECT_EQ(dandan->getCurrentAbilities().size(), 1);
    EXPECT_TRUE(dandan::core::isFlyingAbility(
        dandan->getCurrentAbilities()[0].definition()));
    EXPECT_EQ(dandan->getPower(), 4);
    EXPECT_EQ(dandan->getToughness(), 4);
    EXPECT_EQ(dandan->getCurrentSubTypes(), expected_subtypes);
    EXPECT_EQ(condition_manager.size(), 0);
    EXPECT_EQ(replacement_manager.size(), 0);
    EXPECT_EQ(event_manager.size(), 0);
    EXPECT_EQ(prevention_manager.size(), EXPECTED_NUM_PREVENTIONS);
}

TEST(DandanLibTest, DanceOfTheSkywiseExpiresTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_DANDANS{4};
    static constexpr int NUM_ISLANDS{4};
    static constexpr int NUM_DANCE{30};

    auto dandan_abilities{::Dandan_Abilities()};
    auto island_abilities{::Island_TESTS_Abilities()};
    auto dance_abilities{::Dance_of_the_Skywise_Abilities()};

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
                               dandan::core::Stats{4, 1},
                               dandan::core::ColorWord::Blue}};

    auto mind_bend_data{
        dandan::core::CardData{"Dance of the Skywise",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Instant,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(dance_abilities),
                               std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto dandan_cards{createTestCards(NUM_DANDANS, &dandan_data)};
    auto dance_cards{createTestCards(NUM_DANCE, &mind_bend_data)};

    cards.insert(cards.end(), dandan_cards.begin(), dandan_cards.end());
    cards.insert(cards.end(), dance_cards.begin(), dance_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};
    std::stringstream stream{};

    auto island_1_1{game_state.activePlayer().hand().getCards()[0].getID()};

    auto island_1_2{game_state.activePlayer().hand().getCards()[1].getID()};

    auto island_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};

    auto dandan_1_1{game_state.activePlayer().hand().getCards()[2].getID()};
    auto dance_1_1{game_state.activePlayer().hand().getCards()[4].getID()};

    auto discard_2_1{
        game_state.nonActivePlayer().hand().getCards().back().getID()};

    // turn 1 player 1
    stream << "play " << island_1_1 << '\n';
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << island_2_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 1
    stream << "play " << island_1_2 << '\n';
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << dandan_1_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 2
    stream << "pass\n";
    stream << discard_2_1 << '\n';

    // turn 3 player 1
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << dance_1_1 << '\n';
    stream << "0\n"; // choose dandan as target
    stream << "pass\n";

    // turn 3 player 2
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *dandan{card_registry[dandan_1_1]};
    auto expected_subtypes{std::vector{dandan::core::SubType::Fish}};

    EXPECT_EQ(dandan->getColor(), dandan::core::ColorWord::Blue);
    EXPECT_EQ(dandan->getCurrentAbilities().size(), 2);
    EXPECT_FALSE(dandan::core::isFlyingAbility(
        dandan->getCurrentAbilities()[0].definition()));
    EXPECT_FALSE(dandan::core::isFlyingAbility(
        dandan->getCurrentAbilities()[1].definition()));
    EXPECT_EQ(dandan->getToughness(), 1);
    EXPECT_EQ(dandan->getCurrentSubTypes(), expected_subtypes);
}

TEST(DandanLibTest, DanceSavesDandanFromCrystal)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_DANDANS{4};
    static constexpr int NUM_ISLANDS{6};
    static constexpr int NUM_CRYSTAL{2};
    static constexpr int NUM_DANCE{20};

    auto dandan_abilities{::Dandan_Abilities()};
    auto island_abilities{::Island_TESTS_Abilities()};
    auto crystal_abilities{::Crystal_Spray_Abilities()};
    auto dance_abilities{::Dance_of_the_Skywise_Abilities()};

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
            dandan::mana::ManaBag{{dandan::mana::ManaType::BLUE, 1}}, 1},
        dandan::core::Type::Instant,
        {dandan::core::SubType::None},
        dandan::core::SuperType::None,
        std::move(crystal_abilities),
        std::nullopt,
        dandan::core::ColorWord::Blue}};

    auto dandan_data{
        dandan::core::CardData{"Dandan",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Creature,
                               {dandan::core::SubType::Fish},
                               dandan::core::SuperType::None,
                               std::move(dandan_abilities),
                               dandan::core::Stats{4, 1},
                               dandan::core::ColorWord::Blue}};

    auto mind_bend_data{
        dandan::core::CardData{"Dance of the Skywise",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Instant,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(dance_abilities),
                               std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto dandan_cards{createTestCards(NUM_DANDANS, &dandan_data)};
    auto crystal_cards{createTestCards(NUM_CRYSTAL, &crystal_data)};
    auto dance_cards{createTestCards(NUM_DANCE, &mind_bend_data)};

    cards.insert(cards.end(), dandan_cards.begin(), dandan_cards.end());
    cards.insert(cards.end(), crystal_cards.begin(), crystal_cards.end());
    cards.insert(cards.end(), dance_cards.begin(), dance_cards.end());

    EXPECT_EQ(cards.size(),
              NUM_DANCE + NUM_CRYSTAL + NUM_DANDANS + NUM_ISLANDS);

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

    auto dandan_1_1{game_state.activePlayer().hand().getCards()[3].getID()};

    auto crystal_1_1{
        game_state.activePlayer()
            .hand()
            .getCards()[5] // NOLINT(cppcoreguidelines-avoid-magic-numbers,
                           // readability-magic-numbers)
            .getID()};

    auto dance_2_1{
        game_state.nonActivePlayer()
            .hand()
            .getCards()[6] // NOLINT(cppcoreguidelines-avoid-magic-numbers,
                           // readability-magic-numbers)
            .getID()};

    // turn 1 player 1
    stream << "play " << island_1_1 << '\n';
    stream << "pass\n";

    // turn 1 player 2
    stream << "play " << island_2_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 1
    stream << "play " << island_1_2 << '\n';
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "play " << dandan_1_1 << '\n';
    stream << "pass\n"; // pass turn

    // turn 2 player 2
    stream << "play " << island_2_2 << '\n';
    stream << "pass\n";

    // turn 3 player 1

    stream << "play " << island_1_3 << '\n';
    stream << "activate " << island_1_1 << '\n';
    stream << "activate " << island_1_2 << '\n';
    stream << "activate " << island_1_3 << '\n';

    stream << "play " << crystal_1_1 << '\n';
    stream << 3
           << '\n'; // index 3 of targets for crystal spray to target dandan

    // cast dance in response
    stream << "activate " << island_2_1 << '\n';
    stream << "activate " << island_2_2 << '\n';
    stream << "play " << dance_2_1 << '\n';
    stream << "0\n"; // choose dandan as target

    // choose replacement for resolving crystal spray
    stream << "island\n";
    stream << "swamp\n";

    stream << "pass\n";

    // turn 3 player 2
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    auto *dandan{card_registry[dandan_1_1]};

    EXPECT_EQ(dandan->getZone(), dandan::core::Zone::BATTLEFIELD);
}

// TEST(DandanLibTest, DanceNoSavesDandanFromMindBend)
// {
//     dandan::core::PlayerID::reset();
//
//     static constexpr int NUM_DANDANS{4};
//     static constexpr int NUM_ISLANDS{6};
//     static constexpr int NUM_MIND_BEND{2};
//     static constexpr int NUM_DANCE{20};
//
//     auto dandan_abilities{::Dandan_Abilities()};
//     auto island_abilities{::Island_TESTS_Abilities()};
//     auto mind_bend_abilities{::Mind_Bend_Abilities()};
//     auto dance_abilities{::Dance_of_the_Skywise_Abilities()};
//
//     auto island_data{dandan::core::CardData{
//         "Island", dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
//         dandan::core::Type::Land, dandan::core::SubType::Island,
//         dandan::core::SuperType::Basic,
//         std::move(island_abilities)}};
//
//     auto mind_bend_data{dandan::core::CardData{
//         "Mind Bend",
//         std::make_unique<dandan::mana::AndMana>(
//             std::make_unique<dandan::mana::GenericMana>(2),
//             std::make_unique<dandan::mana::BlueMana>(1)),
//         dandan::core::Type::Instant, dandan::core::SubType::None,
//         dandan::core::SuperType::None,
//         std::move(mind_bend_abilities), std::nullopt,
//         dandan::core::ColorWord::Blue}};
//
//     auto dandan_data{dandan::core::CardData{
//         "Dandan", std::make_unique<dandan::mana::BlueMana>(2),
//         dandan::core::Type::Creature, dandan::core::SubType::Fish,
//         dandan::core::SuperType::None, std::move(dandan_abilities),
//         dandan::core::Stats{4, 1}, dandan::core::ColorWord::Blue}};
//
//     auto dance_data{dandan::core::CardData{
//         "Dance of the Skywise",
//         std::make_unique<dandan::mana::BlueMana>(2),
//         dandan::core::Type::Instant, dandan::core::SubType::None,
//         dandan::core::SuperType::None,
//         std::move(dance_abilities)}};
//
//     auto cards{createTestCards(NUM_ISLANDS, &island_data)};
//     auto dandan_cards{createTestCards(NUM_DANDANS, &dandan_data)};
//     auto dance_cards{createTestCards(NUM_DANCE, &dance_data)};
//     auto mind_bend_cards{createTestCards(NUM_MIND_BEND,
//     &mind_bend_data)};
//
//     cards.insert(cards.end(), dandan_cards.begin(), dandan_cards.end());
//     cards.insert(cards.end(), mind_bend_cards.begin(),
//     mind_bend_cards.end()); cards.insert(cards.end(),
//     dance_cards.begin(), dance_cards.end());
//
//     // cards are dealt one at a time to each player starting with the
//     first
//     // player
//     auto game{dandan::Game::withCards(std::move(cards), false)};
//     auto &game_state{game.execution_context().state.get()};
//     auto &card_registry{game.execution_context().cards.get()};
//     std::stringstream stream{};
//
//     auto island_1_1{game_state.activePlayer().hand().getCards()[0].getID()};
//     auto island_1_2{game_state.activePlayer().hand().getCards()[1].getID()};
//     auto island_1_3{game_state.activePlayer().hand().getCards()[2].getID()};
//
//     auto
//     island_2_1{game_state.nonActivePlayer().hand().getCards()[0].getID()};
//     auto
//     island_2_2{game_state.nonActivePlayer().hand().getCards()[1].getID()};
//
//     auto dandan_1_1{game_state.activePlayer().hand().getCards()[3].getID()};
//
//     auto mind_bend_1_1{
//         game_state.activePlayer()
//             .hand()
//             .getCards()[5] //
//             NOLINT(cppcoreguidelines-avoid-magic-numbers,
//                            // readability-magic-numbers)
//             .getID()};
//
//     auto dance_2_1{
//         game_state.nonActivePlayer()
//             .hand()
//             .getCards()[6] //
//             NOLINT(cppcoreguidelines-avoid-magic-numbers,
//                            // readability-magic-numbers)
//             .getID()};
//
//     // turn 1 player 1
//     stream << "play " << island_1_1 << '\n';
//     stream << "pass\n";
//
//     // turn 1 player 2
//     stream << "play " << island_2_1 << '\n';
//     stream << "pass\n"; // pass turn
//
//     // turn 2 player 1
//     stream << "play " << island_1_2 << '\n';
//     stream << "activate " << island_1_1 << '\n';
//     stream << "activate " << island_1_2 << '\n';
//     stream << "play " << dandan_1_1 << '\n';
//     stream << "pass\n"; // pass turn
//
//     // turn 2 player 2
//     stream << "play " << island_2_2 << '\n';
//     stream << "pass\n";
//
//     // turn 3 player 1
//
//     stream << "play " << island_1_3 << '\n';
//     stream << "activate " << island_1_1 << '\n';
//     stream << "activate " << island_1_2 << '\n';
//     stream << "activate " << island_1_3 << '\n';
//
//     stream << "play " << mind_bend_1_1 << '\n';
//     stream << 3 << '\n'; // index 3 of targets for mind bend to target
//     dandan
//
//     // cast dance in response
//     stream << "activate " << island_2_1 << '\n';
//     stream << "activate " << island_2_2 << '\n';
//     stream << "play " << dance_2_1 << '\n';
//     stream << "0\n"; // choose dandan as target
//
//     // choose replacement for resolving crystal spray
//     stream << "island\n";
//     stream << "swamp\n";
//
//     stream << "pass\n";
//
//     // turn 3 player 2
//     stream << "quit\n";
//
//     game.setIstream(stream);
//     game.run();
//
//     auto *dandan{card_registry(dandan_1_1)};
//
//     for (const auto &ability : dandan->getCurrentAbilities())
//     {
//         auto context{ability.getContext()};
//         EXPECT_TRUE(context.text_replacements.has_value());
//         EXPECT_EQ(context.text_replacements->size(), 1);
//     }
//
//     EXPECT_EQ(dandan->getZone(), dandan::core::Zone::GRAVEYARD);
// }
