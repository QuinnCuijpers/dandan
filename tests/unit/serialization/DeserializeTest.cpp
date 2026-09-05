#include <gtest/gtest.h>
#ifdef DANDAN_SERIALIZE
#include "DeserializeTest.h"
#include <fstream>
#include <nlohmann/json.hpp>

void DeserializeTest::SetUp()
{
    const auto &params{GetParam()};
    const auto card = params;
    std::string_view name{card.getData().name};

    auto json_file_path{std::filesystem::path{DANDAN_PROJECT_SOURCE} /
                        "data/jsons" / name};
    json_file_path += ".json";

    std::ifstream file{json_file_path};
    nlohmann::json json{};
    file >> json;

    m_expected = json;
    m_received = nlohmann::json(card.getData());
}

TEST_P(DeserializeTest, DeserializeCorrect)
{
    EXPECT_EQ(m_received, m_expected);
}

#endif
