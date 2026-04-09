#include "dandan/dandan.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <string_view>
#include <vector>
#include <iostream>
#include <fstream>

static std::vector<std::unique_ptr<dandan::IAbility>> islandAbilities()
{
    auto res{std::vector<std::unique_ptr<dandan::IAbility>>{}};
    res.push_back(
        std::make_unique<dandan::ManaAbility>(dandan::ManaAbility::BLUE));
    return res;
}

static const dandan::Card *CARDS[] = {
    new dandan::Card{"Island", 0, dandan::Card::Land, islandAbilities()}};

class JsonTest : public testing::TestWithParam<const dandan::Card *>
{

protected:
    dandan::Card m_recieved{};
    const dandan::Card *m_expected{};

    void SetUp() override
    {
        auto params{GetParam()};
        m_expected = params;
        std::string_view name{m_expected->get_name()};

        auto json_file_path{std::filesystem::path{DANDAN_SOURCE_DIR} /
                            "data/jsons" / name};
        json_file_path += ".json";
        std::cout << json_file_path << '\n';

        std::ifstream file{json_file_path};
        nlohmann::json j{};
        file >> j;
        m_recieved = j.get<dandan::Card>();
    }
};

TEST_P(JsonTest, DeserializeCorrect)
{
    std::cout << m_recieved.get_name() << '\n';
    EXPECT_EQ(m_recieved.get_name(), m_expected->get_name());
};

INSTANTIATE_TEST_SUITE_P(DeserializationTests, JsonTest,
                         testing::ValuesIn(CARDS));
