#include "common.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/Constants.h"
#include "dandan/core/Player.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/Zone.h"
#include "dandan/dandan.h"
#include "dandan/mana/BlueMana.h"
#include "dandan/mana/GenericMana.h"
#include <algorithm>
#include <array>
#include <cstddef>
#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "LandDefinitions.h"
#include "TestCardsCreate.h"

static constexpr int TEST_DECK_SIZE{20};

TEST(DandanLibTest, GameSetup)
{
    dandan::core::PlayerID::reset();
    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};

    auto &active_player = game.activePlayer();

    std::vector<std::string> card_names;
    std::transform(
        active_player.hand().getCards().begin(),
        active_player.hand().getCards().end(), std::back_inserter(card_names),
        [&game](const auto &card)
        { return std::string(game.getCardByID(card)->getData().getName()); });

    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        auto card_id = active_player.hand().getCards().front();
        auto *card = game.getCardByID(card_id);
        active_player.playCard(*card);
    }

    std::vector<std::string> battlefield_card_names{};

    auto getCardname = [&game](const auto &card)
    { return std::string(game.getCardByID(card)->getData().getName()); };

    for (const auto &[type, cards] : active_player.battlefield().permanents())
    {
        std::transform(cards.begin(), cards.end(),
                       std::back_inserter(battlefield_card_names), getCardname);
    }

    EXPECT_EQ(card_names, battlefield_card_names);
}

TEST(DandanLibTest, NoDrawFirstTurn)
{
    dandan::core::PlayerID::reset();
    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    auto game{dandan::Game::withCards(std::move(test_cards))};

    auto &active_player = game.activePlayer();
    auto &non_active_player = game.nonActivePlayer();

    EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE);
    EXPECT_EQ(non_active_player.hand().getCards().size(), STARTING_HAND_SIZE);

    game.handlePhase();
    // Active player should not draw a card on the first turn
    EXPECT_EQ(active_player.hand().getCards().size(), STARTING_HAND_SIZE);
    // Non active player should draw a card on the first turn
    game.passTurn();
    game.handlePhase();
    EXPECT_EQ(non_active_player.hand().getCards().size(),
              STARTING_HAND_SIZE + 1);
}

TEST(DandanLibTest, Bounceland)
{
    dandan::core::PlayerID::reset();

    auto abilities{Izzet_Boilerworks_Abilities()};

    auto data = dandan::core::CardData{
        "Test Card ", std::make_unique<dandan::mana::GenericMana>(0),
        dandan::core::CardData::Type::Land,
        dandan::core::CardData::SubType::Island, std::move(abilities)};

    auto test_cards = createTestCards(TEST_DECK_SIZE, &data);
    std::stringstream stream{};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    // first player
    stream << "play " << game.activePlayer().hand().getCards().front().getID()
           << "\n";
    stream << "0\n";
    stream << "pass\n";

    // second player

    stream << "play "
           << game.nonActivePlayer().hand().getCards().front().getID() << '\n';
    stream << "0\n";
    stream << "pass\n";
    stream << game.nonActivePlayer().hand().getCards().front().getID() << '\n';

    stream << "play " << game.activePlayer().hand().getCards().front().getID()
           << '\n';
    stream << "0\n";
    stream << "pass\n";
    stream << game.activePlayer().hand().getCards().front().getID() << '\n';

    stream << "quit\n";

    game.setIstream(stream);

    game.run();

    EXPECT_EQ(game.graveyard().getCards().size(), 2);
}

TEST(DandanLibTest, Play1LandATurnTest)
{

    dandan::core::PlayerID::reset();
    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};
    std::stringstream input_stream{};
    const auto &hand_cards = game.activePlayer().hand().getCards();
    for (int i{}; i < STARTING_HAND_SIZE; ++i)
    {
        input_stream << "play " << hand_cards[i].getID() << '\n';
    }
    input_stream << "quit\n";
    game.setIstream(input_stream);

    game.run();

    // only one land should be played since the second play should be prevented
    EXPECT_EQ(game.activePlayer().battlefield().getLands().size(), 1);
}

TEST(DandanLibTest, DiscardToHandSize)
{
    dandan::core::PlayerID::reset();

    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    std::stringstream stream{};
    for (size_t i{}; i < dandan::core::AMOUNT_PLAYERS; ++i)
    {
        stream << "pass\n";
    }
    // the non-active player will be the one prompted to discard on cleanup
    stream << game.nonActivePlayer().hand().getCards().front().getID() << '\n';
    stream << "quit\n";

    game.setIstream(stream);

    game.run();

    // TODO:
    //  both players should be down to 7 cards in hand after discarding down to
    //  hand size at the end of the turn
    //  quit is only chosen in main phase for now, so active player has
    //  STARTING_HAND_SIZE + 1 as they drew for turn
    EXPECT_EQ(game.activePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE + 1);
    EXPECT_EQ(game.nonActivePlayer().hand().getCards().size(),
              STARTING_HAND_SIZE);
}

TEST(DandanLibTest, PlayCreatureTest)
{
    dandan::core::PlayerID::reset();

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>()};

    auto data = dandan::core::CardData{
        "Test Card ", std::make_unique<dandan::mana::BlueMana>(2),
        dandan::core::CardData::Type::Creature,
        dandan::core::CardData::SubType::None, std::move(abilities)};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    std::stringstream stream{};
    const auto &hand_cards = game.activePlayer().hand().getCards();
    for (size_t i{}; i < STARTING_HAND_SIZE - 1; ++i)
    {
        auto card_id = hand_cards[i];
        stream << "play " << card_id.getID() << '\n';
    }
    stream << "quit\n";
    game.setIstream(stream);

    // beginning phase
    game.handlePhase();

    // main phase
    game.activePlayer().manaPool().addMana(dandan::mana::ManaType::BLUE,
                                           2 * (STARTING_HAND_SIZE - 1));

    // should play 6 dandan
    game.run();

    // player should have the mana that was added to their mana pool
    EXPECT_EQ(game.activePlayer().battlefield().getCreatures().size(),
              STARTING_HAND_SIZE - 1);
}

TEST(DandanLibTest, ActivateCyclingAbilityTest)
{
    dandan::core::PlayerID::reset();

    auto abilities{Remote_Isle_Abilities()};

    auto data = dandan::core::CardData{
        "Test Card ", std::make_unique<dandan::mana::BlueMana>(0),
        dandan::core::CardData::Type::Land,
        dandan::core::CardData::SubType::None, std::move(abilities)};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    std::stringstream stream{};
    const auto &hand_cards = game.activePlayer().hand().getCards();
    for (size_t i{}; i < STARTING_HAND_SIZE - 1; ++i)
    {
        auto card_id = hand_cards[i];
        stream << "activate " << card_id.getID() << '\n';
    }
    stream << "quit\n";
    game.setIstream(stream);

    // beginning phase
    game.handlePhase();

    // main phase
    game.activePlayer().manaPool().addMana(dandan::mana::ManaType::BLUE,
                                           2 * (STARTING_HAND_SIZE - 1));

    // should activate 6 cycling abilities
    game.run();

    auto size = game.library().getCards().size();
    std::cout << "Library size: " << size << '\n';
    EXPECT_EQ(size, TEST_DECK_SIZE - (2 * STARTING_HAND_SIZE) -
                        (STARTING_HAND_SIZE - 1));
}

TEST(DandanLibTest, CombatTest)
{
    dandan::core::PlayerID::reset();

    auto abilities{std::vector<std::unique_ptr<dandan::abilities::IAbility>>()};

    auto data =
        dandan::core::CardData{"Test Card ",
                               std::make_unique<dandan::mana::BlueMana>(0),
                               dandan::core::CardData::Type::Creature,
                               dandan::core::CardData::SubType::None,
                               std::move(abilities),
                               dandan::core::Stats{4, 3}};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    std::stringstream stream{};

    auto attacker_id{game.activePlayer().hand().getCards().front()};
    auto defender_id{game.nonActivePlayer().hand().getCards().front()};

    // play creature for active player and pass
    stream << "play " << attacker_id.getID() << '\n';
    stream << "next\n"; // should move to combat phase where player can choose
                        // to attack with creature with summoning sickness
    stream << "pass\n";

    // play creature for non active player and pass
    stream << "play " << defender_id.getID() << '\n';
    stream << "next\n"; // should not find any attackers and move to next main
                        // phase
    stream << "pass\n";

    // combat phase player 1
    stream << "next\n"; // pass to combat phase
    stream << "0\n";    // choose the first creature as attacker
    stream << attacker_id.getID()
           << '\n';     // choose to block the attacking creature
    stream << "pass\n"; // pass to next player

    // quit
    stream << "quit\n"; // quit to avoid discard logic

    game.setIstream(stream);

    // combat phase, should not be able to attack with creatures due to
    // summoning sickness
    game.run();

    EXPECT_EQ(game.activePlayer().battlefield().getCreatures().size(), 0);
    EXPECT_EQ(game.nonActivePlayer().battlefield().getCreatures().size(), 0);

    const auto *attacking_creature = game.getCardByID(attacker_id);
    const auto *blocking_creature = game.getCardByID(defender_id);

    // both creatures should have died in combat
    EXPECT_EQ(game.graveyard().getCards().size(), 2);

    EXPECT_EQ(attacking_creature->getZone(), dandan::core::Zone::GRAVEYARD);
    EXPECT_EQ(blocking_creature->getZone(), dandan::core::Zone::GRAVEYARD);

    // neither creature should be marked as attacking or blocking since they
    // should have died
    EXPECT_FALSE(attacking_creature->isAttacking());
    EXPECT_FALSE(blocking_creature->isAttacking());

    EXPECT_FALSE(attacking_creature->isBlocked());
    EXPECT_FALSE(blocking_creature->isBlocking());

    EXPECT_EQ(attacking_creature->getDamageMarked(), 0);
    EXPECT_EQ(blocking_creature->getDamageMarked(), 0);
}

TEST(DandanLibTest, ManaAbilities)
{
    dandan::core::PlayerID::reset();

    std::vector<dandan::Card> lands{
        LAND(Island, dandan::CardData::SubType::Island),
        LAND(Remote_Isle, dandan::CardData::SubType::None),
        LAND(Lonely_Sandbar, dandan::CardData::SubType::None),
        LAND(Shivan_Reef, dandan::CardData::SubType::None),
        LAND(Temple_of_Epiphany, dandan::CardData::SubType::None),
        LAND(Izzet_Boilerworks, dandan::CardData::SubType::None),
        LAND(Svyelunite_Temple, dandan::CardData::SubType::None)};

    std::unordered_map<std::string, bool> requires_option{
        {"Island", false},
        {"Remote Isle", false},
        {"Lonely Sandbar", false},
        {"Shivan Reef", true},
        {"Temple of Epiphany", true},
        {"Izzet Boilerworks", false},
        {"Svyelunite Temple", true}};

    std::unordered_map<std::string, size_t> desired_option{
        {"Shivan Reef", 2},
        {"Temple of Epiphany", 1},
        {"Svyelunite Temple", 1}};

    auto game{dandan::Game::withCards(std::move(lands))};

    // add n copies of a land to each players battlefield where n is the
    // amount
    // of options for the player to choose from when activating mana
    // abilities
    for (auto &player : game.getPlayers())
    {
        for (const auto &land : player.hand().getCards())
        {
            auto *card{game.getCardByID(land)};
            // Adds a copy of the land in hand to the battlefield
            player.playCard(*card);
        }
    }

    std::stringstream stream{};

    for (auto &player : game.getPlayers())
    {
        for (const auto &permanent : player.battlefield().getLands())
        {
            auto *card{game.getCardByID(permanent)};
            stream << "activate " << card->getID().getID() << '\n';
            if (requires_option[std::string(card->getData().getName())])
            {
                stream << desired_option[std::string(card->getData().getName())]
                       << '\n';
            }
        }
    }
    stream << "quit\n";

    game.setIstream(stream);
    game.run();
}

TEST(DandanLibTest, TempleOfEpiphanyTest)
{
    dandan::core::PlayerID::reset();

    auto abilities{Temple_of_Epiphany_Abilities()};

    auto data = dandan::core::CardData{
        "Test Card ", std::make_unique<dandan::mana::GenericMana>(0),
        dandan::core::CardData::Type::Land,
        dandan::core::CardData::SubType::None, std::move(abilities)};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    std::stringstream stream{};

    auto next_top_card_id{game.library().getCards().front()};
    auto next_next_top_card_id{game.library().getCards()[1]};

    stream << "play " << game.activePlayer().hand().getCards().front().getID()
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

    EXPECT_EQ(game.activePlayer().battlefield().getLands().size(), 1);
    EXPECT_EQ(game.activePlayer().battlefield().getLands().front(),
              next_top_card_id); // scryed to top

    EXPECT_EQ(game.library().getCards().back(),
              next_next_top_card_id); // scryed to bottom
}

TEST(DandanLibTest, HalimarDepthsAbilities)
{
    dandan::core::PlayerID::reset();

    auto abilities{Halimar_Depths_Abilities()};

    auto data = dandan::core::CardData{
        "Test Card ", std::make_unique<dandan::mana::GenericMana>(0),
        dandan::core::CardData::Type::Land,
        dandan::core::CardData::SubType::None, std::move(abilities)};

    auto test_cards{createTestCards(TEST_DECK_SIZE, &data)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    std::stringstream stream{};

    // auto top_1{game.library().getCards().front()};
    auto top_2{game.library().getCards()[1]};
    auto top_3{game.library().getCards()[2]};
    // auto top_4{game.library().getCards()[3]};

    stream << "play " << game.activePlayer().hand().getCards().front().getID()
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

TEST(DandanLibTest, DieFromEmptyLibrary)
{
    dandan::core::PlayerID::reset();

    const int MIN_LIB_SIZE = 14;
    auto test_cards{createTestCards(MIN_LIB_SIZE)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    std::stringstream stream{};

    // pass until the library is empty and the active player tries to draw from
    // an empty library
    stream << "pass\n"; // first player passes, second player draws for turn and
                        // dies, game should end before the second player can
                        // input anything

    game.setIstream(stream);
    game.run();

    EXPECT_TRUE(game.activePlayer().lost());
}

TEST(DandanLibTest, DieFromNoLife)
{
    dandan::core::PlayerID::reset();

    auto test_cards{createTestCards(TEST_DECK_SIZE)};
    dandan::core::Game game{dandan::Game::withCards(std::move(test_cards))};

    game.activePlayer().takeDamage(game.activePlayer().getLifeTotal(), game);
    game.run();

    EXPECT_TRUE(game.activePlayer().lost());
}