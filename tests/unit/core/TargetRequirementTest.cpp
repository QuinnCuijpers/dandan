
#include "dandan/core/TargetRequirement.h"
#include <gtest/gtest.h>
#include <tuple>

using TargetTypeCase = std::tuple<dandan::core::TargetType, std::string>;

const std::vector<TargetTypeCase> &targetTypeCases()
{
    static const std::vector<TargetTypeCase> cases{
        {dandan::core::TargetType::Player, "Player"},
        {dandan::core::TargetType::Creature, "Creature"},
        {dandan::core::TargetType::Land, "Land"},
        {dandan::core::TargetType::Permanent, "Permanent"},
        {dandan::core::TargetType::Spell, "Spell"},
        {dandan::core::TargetType::Planeswalker, "Planeswalker"},
        {dandan::core::TargetType::Card, "Card"},
        {dandan::core::TargetType::Any, "Any"},
    };
    return cases;
}

class TargetTypeToStringTest : public testing::TestWithParam<TargetTypeCase>
{
};

TEST_P(TargetTypeToStringTest, ReturnsExpectedString)
{
    const auto &[type, expected] = GetParam();
    EXPECT_EQ(dandan::core::targetTypeToString(type), expected);
}

INSTANTIATE_TEST_SUITE_P(AllTargetTypes, TargetTypeToStringTest,
                         testing::ValuesIn(targetTypeCases()));
