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
        new LAND(Island, Island, Basic),
        new LAND(Remote_Isle, None, None),
        new LAND(Lonely_Sandbar, None, None),
        new LAND(Halimar_Depths, None, None),
        new LAND(Shivan_Reef, None, None),
        new LAND(Temple_of_Epiphany, None, None),
        new LAND(Izzet_Boilerworks, None, None),
        new LAND(Svyelunite_Temple, None, None)};
    return cards;
};

INSTANTIATE_TEST_SUITE_P(
    LandTests, DeserializeTest, testing::ValuesIn(getCards()),
    [](const ::testing::TestParamInfo<const dandan::Card *> &info)
    { return CardParamName(info.param->getData().getName()); });

#endif