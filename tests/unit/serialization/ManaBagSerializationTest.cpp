#ifdef DANDAN_SERIALIZE

#include "dandan/mana/ManaBag.h"
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
    using dandan::mana::ManaType;
    using dandan::serialization::JsonFactory;

    void expectBagEq(const ManaBag &actual, const ManaBag &expected)
    {
        EXPECT_EQ(actual.data(), expected.data());
    }

    struct BagSerializeCase
    {
        ManaBag bag;
        std::string expected;
    };

    class ManaBagSerializeTest : public testing::TestWithParam<BagSerializeCase>
    {
    };

    TEST_P(ManaBagSerializeTest, WritesCanonicalSymbols)
    {
        const auto &[bag, expected] = GetParam();

        EXPECT_EQ(JsonFactory<ManaBag>::create_json(&bag).get<std::string>(),
                  expected);
    }

    INSTANTIATE_TEST_SUITE_P(
        ManaBagSerialize, ManaBagSerializeTest,
        testing::Values(
            BagSerializeCase{ManaBag{}, ""},
            BagSerializeCase{ManaBag{{ManaType::COLORLESS, 1}}, "C"},
            BagSerializeCase{ManaBag{{ManaType::WHITE, 1}}, "W"},
            BagSerializeCase{ManaBag{{ManaType::BLUE, 1}}, "U"},
            BagSerializeCase{ManaBag{{ManaType::BLACK, 1}}, "B"},
            BagSerializeCase{ManaBag{{ManaType::RED, 1}}, "R"},
            BagSerializeCase{ManaBag{{ManaType::GREEN, 1}}, "G"},
            BagSerializeCase{ManaBag{{ManaType::GREEN, 2}, {ManaType::BLUE, 1}},
                             "UGG"},
            BagSerializeCase{ManaBag{{ManaType::BLUE, 1}, {ManaType::BLUE, 2}},
                             "UUU"}));

    struct BagDeserializeCase
    {
        std::string json;
        ManaBag expected;
    };

    class ManaBagDeserializeTest
        : public testing::TestWithParam<BagDeserializeCase>
    {
    };

    TEST_P(ManaBagDeserializeTest, ReadsSymbols)
    {
        const auto &[json, expected] = GetParam();
        const auto actual =
            JsonFactory<ManaBag>::create_product(nlohmann::json(json));

        expectBagEq(actual, expected);
    }

    INSTANTIATE_TEST_SUITE_P(
        ManaBagDeserialize, ManaBagDeserializeTest,
        testing::Values(
            BagDeserializeCase{"", ManaBag{}},
            BagDeserializeCase{"WUBRG", ManaBag{{ManaType::WHITE, 1},
                                                {ManaType::BLUE, 1},
                                                {ManaType::BLACK, 1},
                                                {ManaType::RED, 1},
                                                {ManaType::GREEN, 1}}},
            BagDeserializeCase{"CC", ManaBag{{ManaType::COLORLESS, 2}}},
            BagDeserializeCase{"GUR", ManaBag{{ManaType::GREEN, 1},
                                              {ManaType::BLUE, 1},
                                              {ManaType::RED, 1}}}));

    TEST(ManaBagDeserializeTest, RejectsUnknownSymbol)
    {
        EXPECT_THROW(JsonFactory<ManaBag>::create_product(nlohmann::json("X")),
                     std::runtime_error);
    }

    TEST(ManaBagDeserializeTest, RejectsGenericNotation)
    {
        EXPECT_THROW(
            JsonFactory<ManaBag>::create_product(nlohmann::json("(2)")),
            std::runtime_error);
    }

    TEST(ManaBagSerializationRoundTripTest, RoundTrips)
    {
        const std::vector<ManaBag> bags{
            ManaBag{},
            ManaBag{{ManaType::COLORLESS, 3}},
            ManaBag{{ManaType::WHITE, 2}, {ManaType::GREEN, 1}},
        };

        for (const auto &bag : bags)
        {
            const auto json = JsonFactory<ManaBag>::create_json(&bag);
            expectBagEq(JsonFactory<ManaBag>::create_product(json), bag);
        }
    }
} // namespace

#endif // DANDAN_SERIALIZE
