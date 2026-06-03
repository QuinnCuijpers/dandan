#ifdef DANDAN_SERIALIZE
#include "DeserializeTest.h"
#include "LandDefinitions.h"
#include "common.h"
#include "dandan/dandan.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new LAND(Island, dandan::CardData::SubType::Island),
        new LAND(Remote_Isle, dandan::CardData::SubType::None),
        new LAND(Lonely_Sandbar, dandan::CardData::SubType::None),
        new LAND(Halimar_Depths, dandan::CardData::SubType::None),
        new LAND(Shivan_Reef, dandan::CardData::SubType::None),
        new LAND(Temple_of_Epiphany, dandan::CardData::SubType::None),
        new LAND(Izzet_Boilerworks, dandan::CardData::SubType::None),
        new LAND(Svyelunite_Temple, dandan::CardData::SubType::None)};
    return cards;
};

INSTANTIATE_TEST_SUITE_P(
    LandTests, DeserializeTest, testing::ValuesIn(getCards()),
    [](const ::testing::TestParamInfo<const dandan::Card *> &info)
    { return CardParamName(info.param->getData().getName()); });

#endif