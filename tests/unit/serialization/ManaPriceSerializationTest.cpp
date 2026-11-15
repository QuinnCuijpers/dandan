#ifdef DANDAN_SERIALIZE

#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaPrice.h"
#include "dandan/mana/ManaType.h"
#include "dandan/serialization/JsonFactory.h"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    using dandan::mana::ManaBag;
    using dandan::mana::ManaPrice;
    using dandan::mana::ManaType;
    using dandan::serialization::JsonFactory;

    void expectPriceEq(const ManaPrice &actual, const ManaPrice &expected)
    {
        EXPECT_EQ(actual.generic(), expected.generic());
        EXPECT_EQ(actual.specific().data(), expected.specific().data());
    }

    struct PriceSerializeCase
    {
        ManaPrice price;
        std::string expected;
    };

    class ManaPriceSerializeTest
        : public testing::TestWithParam<PriceSerializeCase>
    {
    };

    TEST_P(ManaPriceSerializeTest, WritesGenericThenSpecific)
    {
        const auto &[price, expected] = GetParam();

        EXPECT_EQ(
            JsonFactory<ManaPrice>::create_json(&price).get<std::string>(),
            expected);
    }

    INSTANTIATE_TEST_SUITE_P(
        ManaPriceSerialize, ManaPriceSerializeTest,
        testing::Values(
            PriceSerializeCase{ManaPrice{}, "(0)"},
            PriceSerializeCase{ManaPrice{ManaBag{}, 2}, "(2)"},
            PriceSerializeCase{ManaPrice{ManaBag{{ManaType::BLUE, 1}}, 0}, "U"},
            PriceSerializeCase{ManaPrice{ManaBag{{ManaType::BLUE, 2}}, 0},
                               "UU"},
            PriceSerializeCase{ManaPrice{ManaBag{{ManaType::RED, 1}}, 2},
                               "(2)R"},
            PriceSerializeCase{ManaPrice{ManaBag{{ManaType::COLORLESS, 2}}, 10},
                               "(10)CC"},
            PriceSerializeCase{
                ManaPrice{ManaBag{{ManaType::GREEN, 1}, {ManaType::BLUE, 1}},
                          3},
                "(3)UG"}));

    struct PriceDeserializeCase
    {
        std::string json;
        ManaPrice expected;
    };

    class ManaPriceDeserializeTest
        : public testing::TestWithParam<PriceDeserializeCase>
    {
    };

    TEST_P(ManaPriceDeserializeTest, ReadsGenericAndSpecific)
    {
        const auto &[json, expected] = GetParam();
        const auto actual =
            JsonFactory<ManaPrice>::create_product(nlohmann::json(json));

        expectPriceEq(actual, expected);
    }

    INSTANTIATE_TEST_SUITE_P(
        ManaPriceDeserialize, ManaPriceDeserializeTest,
        testing::Values(
            PriceDeserializeCase{"(0)", ManaPrice{}},
            PriceDeserializeCase{"U",
                                 ManaPrice{ManaBag{{ManaType::BLUE, 1}}, 0}},
            PriceDeserializeCase{"(2)", ManaPrice{ManaBag{}, 2}},
            PriceDeserializeCase{"(2)R",
                                 ManaPrice{ManaBag{{ManaType::RED, 1}}, 2}},
            PriceDeserializeCase{"WUBRG",
                                 ManaPrice{ManaBag{{ManaType::WHITE, 1},
                                                   {ManaType::BLUE, 1},
                                                   {ManaType::BLACK, 1},
                                                   {ManaType::RED, 1},
                                                   {ManaType::GREEN, 1}},
                                           0}},
            PriceDeserializeCase{
                "(10)CC", ManaPrice{ManaBag{{ManaType::COLORLESS, 2}}, 10}},
            PriceDeserializeCase{
                "(3)UG",
                ManaPrice{ManaBag{{ManaType::BLUE, 1}, {ManaType::GREEN, 1}},
                          3}}));

    TEST(ManaPriceDeserializeTest, RejectsMissingClosingParenthesis)
    {
        EXPECT_THROW(
            JsonFactory<ManaPrice>::create_product(nlohmann::json("(2")),
            std::runtime_error);
    }

    TEST(ManaPriceDeserializeTest, RejectsUnknownSymbol)
    {
        EXPECT_THROW(
            JsonFactory<ManaPrice>::create_product(nlohmann::json("X")),
            std::runtime_error);
    }

    TEST(ManaPriceSerializationRoundTripTest, RoundTrips)
    {
        const std::vector<ManaPrice> prices{
            ManaPrice{},
            ManaPrice{ManaBag{}, 2},
            ManaPrice{ManaBag{{ManaType::RED, 1}}, 2},
            ManaPrice{ManaBag{{ManaType::BLUE, 1}, {ManaType::GREEN, 2}}, 3},
        };

        for (const auto &price : prices)
        {
            const auto json = JsonFactory<ManaPrice>::create_json(&price);
            expectPriceEq(JsonFactory<ManaPrice>::create_product(json), price);
        }
    }
} // namespace

#endif // DANDAN_SERIALIZE
