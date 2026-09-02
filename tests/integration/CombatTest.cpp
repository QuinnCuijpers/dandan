#include "common/LandDefinitions.h"
#include "common/TestCardsCreate.h"
#include "common/common.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, CombatTest)
{
    dandan::core::PlayerID::reset();

    auto island_abilities{Island_TESTS_Abilities()};
    auto island_data{dandan::core::CardData{
        "Island",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::Island},
        dandan::core::SuperType::Basic,
        std::move(island_abilities),
        std::nullopt}};

    // dandan can't attack unless the defending player controls an island
    auto abilities{Dandan_Abilities()};
    dandan::Card island1{&island_data};
    dandan::Card island2{&island_data};

    auto data =
        dandan::core::CardData{"Dandan",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 0}}},
                               dandan::core::Type::Creature,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(abilities),
                               dandan::core::Stats{4, 1}};

    auto dandan_cards{createTestCards(TEST_DECK_SIZE, &data)};
    auto island_cards{std::vector<dandan::Card>{island1, island2}};
    dandan_cards.insert(dandan_cards.end(), island_cards.begin(),
                        island_cards.end());
    auto game{dandan::Game::withCards(std::move(dandan_cards))};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};

    // find the first dandan in both players hands
    auto find_dandan = [&card_registry](const auto &card_id)
    {
        const auto *card = card_registry[card_id];
        return card != nullptr && card->getData().name == "Dandan";
    };
    auto attacker_it{std::find_if(
        game_state.activePlayer().hand().getCards().begin(),
        game_state.activePlayer().hand().getCards().end(), find_dandan)};
    auto defender_it{std::find_if(
        game_state.nonActivePlayer().hand().getCards().begin(),
        game_state.nonActivePlayer().hand().getCards().end(), find_dandan)};

    const auto attacker_id = *attacker_it;
    const auto defender_id = *defender_it;

    game_state.activePlayer().battlefield().addCard(island1);
    game_state.nonActivePlayer().battlefield().addCard(island2);

    std::stringstream stream{};

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
    stream << "quit\n"; // quit to avoid discard logic

    game.setIstream(stream);
    game.run();

    EXPECT_EQ(game_state.activePlayer().battlefield().getCreatures().size(), 0);
    EXPECT_EQ(game_state.nonActivePlayer().battlefield().getCreatures().size(),
              0);

    const auto *attacking_creature{card_registry[attacker_id]};
    const auto *blocking_creature{card_registry[defender_id]};

    // both creatures should have died in combat
    EXPECT_EQ(game_state.graveyard().getCards().size(), 2);

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
