
#include "dandan/core/CardTypes.h"
#include <gtest/gtest.h>
#include <tuple>

using TypeCase = std::tuple<dandan::core::Type, std::string_view>;

class TypeToStringTest : public testing::TestWithParam<TypeCase>
{
};

TEST_P(TypeToStringTest, ReturnsExpectedString)
{
    const auto &[type, expected] = GetParam();
    EXPECT_EQ(dandan::core::TypeToString(type), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AllTypes, TypeToStringTest,
    testing::Values(TypeCase{dandan::core::Type::Land, "Land"},
                    TypeCase{dandan::core::Type::Creature, "Creature"},
                    TypeCase{dandan::core::Type::Sorcery, "Sorcery"},
                    TypeCase{dandan::core::Type::Instant, "Instant"},
                    TypeCase{dandan::core::Type::Enchantment, "Enchantment"},
                    TypeCase{dandan::core::Type::Artifact, "Artifact"},
                    TypeCase{dandan::core::Type::Planeswalker,
                             "Planeswalker"}));

using SubTypeCase = std::tuple<dandan::core::SubType, std::string_view>;

class SubTypeToStringTest : public testing::TestWithParam<SubTypeCase>
{
};

TEST_P(SubTypeToStringTest, ReturnsExpectedString)
{
    const auto &[subtype, expected] = GetParam();
    EXPECT_EQ(dandan::core::SubTypeToString(subtype), expected);
}

INSTANTIATE_TEST_SUITE_P(
    AllSubTypes, SubTypeToStringTest,
    testing::Values(SubTypeCase{dandan::core::SubType::None, "None"},
                    SubTypeCase{dandan::core::SubType::Forest, "Forest"},
                    SubTypeCase{dandan::core::SubType::Island, "Island"},
                    SubTypeCase{dandan::core::SubType::Mountain, "Mountain"},
                    SubTypeCase{dandan::core::SubType::Plains, "Plains"},
                    SubTypeCase{dandan::core::SubType::Swamp, "Swamp"},
                    SubTypeCase{dandan::core::SubType::Fish, "Fish"},
                    SubTypeCase{dandan::core::SubType::Illusion, "Illusion"},
                    SubTypeCase{dandan::core::SubType::Dragon, "Dragon"}));
