#include "common/LandDefinitions.h"
#include "common/TestCardsCreate.h"
#include "common/common.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

TEST(DandanLibTest, ManaAbilities)
{
    dandan::core::PlayerID::reset();
    std::vector<std::unique_ptr<dandan::CardData>> land_data;

    land_data.push_back(create_land_data(
        "Island", dandan::core::SuperType::Basic, dandan::core::SubType::None,
        Island_TESTS_Abilities()));

    land_data.push_back(
        create_land_data("Remote_Isle", dandan::core::SuperType::None,
                         dandan::core::SubType::None, Remote_Isle_Abilities()));

    land_data.push_back(create_land_data(
        "Lonely_Sandbar", dandan::core::SuperType::None,
        dandan::core::SubType::None, Lonely_Sandbar_Abilities()));

    land_data.push_back(
        create_land_data("Shivan_Reef", dandan::core::SuperType::None,
                         dandan::core::SubType::None, Shivan_Reef_Abilities()));

    land_data.push_back(create_land_data(
        "Temple_of_Epiphany", dandan::core::SuperType::None,
        dandan::core::SubType::None, Temple_of_Epiphany_Abilities()));

    land_data.push_back(create_land_data(
        "Izzet_Boilerworks", dandan::core::SuperType::None,
        dandan::core::SubType::None, Izzet_Boilerworks_Abilities()));

    land_data.push_back(create_land_data(
        "Svyelunite_Temple", dandan::core::SuperType::None,
        dandan::core::SubType::None, Svyelunite_Temple_Abilities()));

    std::vector<dandan::Card> lands{};
    lands.reserve(land_data.size());

    std::transform(land_data.begin(), land_data.end(),
                   std::back_inserter(lands), [](const auto &data)
                   { return dandan::core::Card{data.get()}; });

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

    auto padded{createTestCards(2 * TEST_DECK_SIZE)};
    lands.insert(lands.end(), padded.begin(), padded.end());

    auto game{dandan::Game::withCards(std::move(lands), false)};
    auto &game_state{game.execution_context().state.get()};
    auto &card_registry{game.execution_context().cards.get()};

    for (auto &player : game_state.getPlayers())
    {
        for (const auto &land : player.hand().getCards())
        {
            auto *card{card_registry[land]};
            // Adds a copy of the land in hand to the battlefield
            player.playCard(*card);
            game_state.moveCardFromZone(player, *card);
        }
    }

    std::stringstream stream{};

    // starting player
    for (const auto &permanent :
         game_state.activePlayer().battlefield().getLands())
    {
        auto *card{card_registry[permanent]};
        stream << "activate " << card->getID().getID() << '\n';
        if (requires_option[std::string(card->getData().name)])
        {
            stream << desired_option[std::string(card->getData().name)] << '\n';
        }
    }

    stream << "pass\n";

    // non active player
    for (const auto &permanent :
         game_state.nonActivePlayer().battlefield().getLands())
    {
        auto *card{card_registry[permanent]};
        stream << "activate " << card->getID().getID() << '\n';
        if (requires_option[std::string(card->getData().name)])
        {
            stream << desired_option[std::string(card->getData().name)] << '\n';
        }
    }
    stream << "quit\n";

    game.setIstream(stream);
    game.run();
}
