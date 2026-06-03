#ifdef DANDAN_SERIALIZE
#include "DeserializeTest.h"
#include "common.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

#include "CreatureDefinitions.h"

static const std::vector<const dandan::Card *> &getCards()
{
    static const std::vector<const dandan::Card *> cards = {
        new CREATURE(Dandan)};
    return cards;
};

INSTANTIATE_TEST_SUITE_P(
    CreatureTests, DeserializeTest, testing::ValuesIn(getCards()),
    [](::testing::TestParamInfo<const dandan::Card *> info)
    { return CardParamName(info.param->getData().getName()); });

#endif