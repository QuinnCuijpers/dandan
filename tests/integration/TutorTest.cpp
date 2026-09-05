#include "common/LandDefinitions.h"
#include "common/SpellDefinitions.h"
#include "common/TestCardsCreate.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, MysticalTutorTest)
{
    dandan::core::PlayerID::reset();

    static constexpr int NUM_ISLANDS{6};
    static constexpr int NUM_TUTORS{35};

    auto island_abilities{::Island_TESTS_Abilities()};
    auto mystical_tutor_abilities{::Mystical_Tutor_Abilities()};

    auto island_data{dandan::core::CardData{
        "Svyelunite Temple",
        dandan::mana::ManaPrice{dandan::mana::ManaBag{}, 0},
        dandan::core::Type::Land,
        {dandan::core::SubType::Island},
        dandan::core::SuperType::Basic,
        std::move(island_abilities),
        std::nullopt}};

    auto mystical_tutor_data{
        dandan::core::CardData{"Mystical Tutor",
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 1}}},
                               dandan::core::Type::Instant,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(mystical_tutor_abilities),
                               std::nullopt}};

    auto cards{createTestCards(NUM_ISLANDS, &island_data)};
    auto mystical_tutor_cards{
        createTestCards(NUM_TUTORS, &mystical_tutor_data)};
    cards.insert(cards.end(), mystical_tutor_cards.begin(),
                 mystical_tutor_cards.end());

    // cards are dealt one at a time to each player starting with the first
    // player
    auto game{dandan::Game::withCards(std::move(cards), false)};
    auto &game_state{game.execution_context().state.get()};

    auto &card_registry{game.execution_context().cards.get()};

    const dandan::core::CardID CHOSEN_CARD_ID{
        game_state.library().getCards().back()};

    std::stringstream stream{};

    auto island_id_1{game_state.activePlayer().hand().getCards()[0]};

    auto mystical_tutor_id{*std::find_if(
        game_state.activePlayer().hand().getCards().begin(),
        game_state.activePlayer().hand().getCards().end(),
        [&card_registry](const auto &card_id)
        {
            const auto *card = card_registry[card_id];
            return card != nullptr && card->getData().name == "Mystical Tutor";
        })};

    // turn 1 player 1
    stream << "play " << island_id_1.getID() << '\n'; // play land
    stream << "activate " << island_id_1.getID()
           << '\n'; // activate land for mana
    stream << "play " << mystical_tutor_id.getID()
           << '\n';                           // play mystical tutor
    stream << CHOSEN_CARD_ID.getID() << '\n'; // choose the card to tutor for
    stream << "pass\n";

    // turn 1 player 2
    stream << "quit\n";

    game.setIstream(stream);
    game.run();

    EXPECT_EQ(game_state.activePlayer().hand().getCards().back().getID(),
              CHOSEN_CARD_ID.getID());
}
