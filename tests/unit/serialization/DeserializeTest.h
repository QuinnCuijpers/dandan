#ifndef DANDAN_TESTS_SERIALIZATION_COMMON_H
#define DANDAN_TESTS_SERIALIZATION_COMMON_H

#ifdef DANDAN_SERIALIZE

#include "dandan/dandan.h"
#include "gtest/gtest.h"
#include <fstream>
#include <nlohmann/json.hpp>

class DeserializeTest : public testing::TestWithParam<const dandan::Card *>
{

public:
    nlohmann::json m_expected;
    nlohmann::json m_received;

protected:
    void SetUp() override
    {
        const auto *params{GetParam()};
        const auto *card = params;
        std::string_view name{card->getData().getName()};

        auto json_file_path{std::filesystem::path{DANDAN_PROJECT_SOURCE} /
                            "data/jsons" / name};
        json_file_path += ".json";

        std::ifstream file{json_file_path};
        nlohmann::json json{};
        file >> json;

        m_expected = json;
        m_received = nlohmann::json(card->getData());
    }
};

#endif

#endif