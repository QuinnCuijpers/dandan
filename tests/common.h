#ifndef DANDAN_TESTS_COMMON_H
#define DANDAN_TESTS_COMMON_H

#include <algorithm>
#include <gtest/gtest.h>
#include <string>

inline std::string CardParamName(const std::string_view raw_name)
{
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