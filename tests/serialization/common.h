#ifndef DANDAN_TESTS_SERIALIZATION_COMMON_H
#define DANDAN_TESTS_SERIALIZATION_COMMON_H

#include "dandan/dandan.h"
#include "gtest/gtest.h"
#include <fstream>
#include <string>

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
        std::string_view name{card->getName()};

        auto json_file_path{std::filesystem::path{DANDAN_PROJECT_SOURCE} /
                            "data/jsons" / name};
        json_file_path += ".json";

        std::ifstream file{json_file_path};
        nlohmann::json json{};
        file >> json;

        m_expected = json;
        m_received = nlohmann::json(*card);
    }
};

inline std::string CardParamName(
    const testing::TestParamInfo<const dandan::Card *> &info)
{
    const std::string raw_name{info.param->getName()};
    std::string name;
    std::copy_if(raw_name.begin(), raw_name.end(), std::back_inserter(name),
                 [](char char_) { return std::isalnum(char_); });
    if (name.empty())
    {
        name = "unnamed";
    }
    return name;
}

inline static std::string formatCardName(std::string_view name)
{
    std::string result{};
    for (char char_ : name)
    {
        if (char_ == '_')
        {
            result += ' ';
        }
        else
        {
            result += char_;
        }
    }
    return result;
}

#endif