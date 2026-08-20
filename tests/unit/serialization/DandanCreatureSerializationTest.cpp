#include "dandan/core/Card.h"
#include <algorithm>
#include <iterator>
#include <memory>
#ifdef DANDAN_SERIALIZE
#include "DeserializeTest.h"
#include "common.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>

static std::vector<dandan::Card> getCards()
{
    std::vector<dandan::Card> cards{};

    static auto card_data = []
    {
        std::vector<std::unique_ptr<dandan::CardData>> card_data{};
        card_data.emplace_back(create_creature_data("Dandan"));
        return card_data;
    }();

    std::transform(card_data.begin(), card_data.end(),
                   std::back_inserter(cards), [](const auto &data)
                   { return dandan::core::Card{data.get()}; });
    return cards;
};

INSTANTIATE_TEST_SUITE_P(CreatureTests, DeserializeTest,
                         testing::ValuesIn(getCards()),
                         [](const ::testing::TestParamInfo<dandan::Card> &info)
                         { return CardParamName(info.param.getData().name); });

#endif
