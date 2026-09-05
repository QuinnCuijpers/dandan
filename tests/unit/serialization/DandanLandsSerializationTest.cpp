
#ifdef DANDAN_SERIALIZE
#include "DeserializeTest.h"
#include "common/LandDefinitions.h"
#include "common/common.h"
#include "dandan/dandan.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <iterator>
#include <memory>
#include <vector>

static std::vector<dandan::Card> getCards()
{
    auto cards = std::vector<dandan::Card>{};

    static auto card_data = []
    {
        std::vector<std::unique_ptr<dandan::CardData>> card_data;

        card_data.push_back(create_land_data(
            "Island", dandan::core::SuperType::Basic,
            dandan::core::SubType::Island, Island_Abilities()));

        card_data.push_back(create_land_data(
            "Remote Isle", dandan::core::SuperType::None,
            dandan::core::SubType::None, Remote_Isle_Abilities()));

        card_data.push_back(create_land_data(
            "Lonely Sandbar", dandan::core::SuperType::None,
            dandan::core::SubType::None, Lonely_Sandbar_Abilities()));

        card_data.push_back(create_land_data(
            "Halimar Depths", dandan::core::SuperType::None,
            dandan::core::SubType::None, Halimar_Depths_Abilities()));

        card_data.push_back(create_land_data(
            "Shivan Reef", dandan::core::SuperType::None,
            dandan::core::SubType::None, Shivan_Reef_Abilities()));

        card_data.push_back(create_land_data(
            "Temple of Epiphany", dandan::core::SuperType::None,
            dandan::core::SubType::None, Temple_of_Epiphany_Abilities()));

        card_data.push_back(create_land_data(
            "Izzet Boilerworks", dandan::core::SuperType::None,
            dandan::core::SubType::None, Izzet_Boilerworks_Abilities()));

        card_data.push_back(create_land_data(
            "Svyelunite Temple", dandan::core::SuperType::None,
            dandan::core::SubType::None, Svyelunite_Temple_Abilities()));

        return card_data;
    }();

    std::transform(card_data.begin(), card_data.end(),
                   std::back_inserter(cards), [](const auto &data)
                   { return dandan::core::Card{data.get()}; });

    return cards;
}

INSTANTIATE_TEST_SUITE_P(LandTests, DeserializeTest,
                         testing::ValuesIn(getCards()),
                         [](const testing::TestParamInfo<dandan::Card> &info)
                         { return CardParamName(info.param.getData().name); });

#endif
