#include "dandan/utils/stringToColorWord.h"
#include "dandan/core/ColorWord.h"
#include <gtest/gtest.h>
#include <tuple>

using StringToColorWordCase = std::tuple<std::string, dandan::core::ColorWord>;

class StringToColorWordParamTest
    : public testing::TestWithParam<StringToColorWordCase>
{
};

TEST_P(StringToColorWordParamTest, ReturnsExpectedColorWord)
{
    const auto &[input, expected] = GetParam();
    EXPECT_EQ(dandan::utils::stringToColorWord(input), expected);
}

INSTANTIATE_TEST_SUITE_P(
    KnownColors, StringToColorWordParamTest,
    testing::Values(
        StringToColorWordCase{"white", dandan::core::ColorWord::White},
        StringToColorWordCase{"blue", dandan::core::ColorWord::Blue},
        StringToColorWordCase{"black", dandan::core::ColorWord::Black},
        StringToColorWordCase{"red", dandan::core::ColorWord::Red},
        StringToColorWordCase{"green", dandan::core::ColorWord::Green}));

TEST(StringToColorWordTest, IsCaseInsensitive)
{
    using dandan::core::ColorWord;

    EXPECT_EQ(dandan::utils::stringToColorWord("WHITE"), ColorWord::White);
    EXPECT_EQ(dandan::utils::stringToColorWord("bLuE"), ColorWord::Blue);
    EXPECT_EQ(dandan::utils::stringToColorWord("Black"), ColorWord::Black);
    EXPECT_EQ(dandan::utils::stringToColorWord("rEd"), ColorWord::Red);
    EXPECT_EQ(dandan::utils::stringToColorWord("GREEN"), ColorWord::Green);
}

TEST(StringToColorWordTest, UnknownInputReturnsColorless)
{
    using dandan::core::ColorWord;

    EXPECT_EQ(dandan::utils::stringToColorWord("purple"), ColorWord::Colorless);
    EXPECT_EQ(dandan::utils::stringToColorWord(""), ColorWord::Colorless);
}
