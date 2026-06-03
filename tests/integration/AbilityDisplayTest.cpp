#ifdef DANDAN_SERIALIZE

#include "common.h"
#include "dandan/dandan.h"
#include <gtest/gtest.h>

struct AbilityDisplayCase
{
    const char *card_name;
    const char *expected_display;
};

class AbilityDisplayTest : public ::testing::TestWithParam<AbilityDisplayCase>
{
};

TEST_P(AbilityDisplayTest, DisplaysExpectedActivatableAbilities)
{
    const auto &test_case = GetParam();
    auto card{dandan::Card{test_case.card_name}};

    std::string actual{};
    for (const auto &ability : card.getData().getAbilities())
    {
        // triggered and static abilities cant be activated, so we ignore them
        // for this test
        if (dynamic_cast<const dandan::abilities::StaticAbility *>(
                ability.get()) != nullptr)
        {
            continue;
        }
        if (dynamic_cast<const dandan::abilities::TriggeredAbility *>(
                ability.get()) != nullptr)
        {
            continue;
        }
        actual += ability->display() + '\n';
    }
    EXPECT_EQ(actual, test_case.expected_display);
}

INSTANTIATE_TEST_SUITE_P(
    ActivatableCards, AbilityDisplayTest,
    ::testing::Values(
        AbilityDisplayCase{
            "Shivan Reef",
            "[T]: Add C\n[T]: Add U or R. This Card deals 1 damage to you\n"},
        AbilityDisplayCase{"Temple of Epiphany", "[T]: Add U or R\n"}),
    [](const ::testing::TestParamInfo<AbilityDisplayCase> &info)
    { return CardParamName(info.param.card_name); });

#endif
