#include "dandan/dandan.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

TEST(UtilTest, ConvertToWords)
{
    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
    auto nums{std::vector<int>{0, 5, 19, 20, 21, 99, 100, 101, 110, 999, 1000,
                               1001, 1010, 1100, 9999}};
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,
    // readability-magic-numbers)
    auto strings{std::vector<std::string>{
        "Zero", "Five", "Nineteen", "Twenty", "Twenty One", "Ninety Nine",
        "One Hundred", "One Hundred One", "One Hundred Ten",
        "Nine Hundred Ninety Nine", "One Thousand", "One Thousand One",
        "One Thousand Ten", "One Thousand One Hundred",
        "Nine Thousand Nine Hundred Ninety Nine"}};
    for (size_t i{}; i < nums.size(); ++i)
    {
        int num{nums[i]};
        std::string expected{"Draw " + strings[i] + " cards"};
        auto draw_effect{std::make_unique<dandan::DrawEffect>(num)};
        EXPECT_EQ(draw_effect->display(), expected);
    }
}