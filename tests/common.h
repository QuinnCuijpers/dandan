#ifndef DANDAN_TESTS_COMMON_H
#define DANDAN_TESTS_COMMON_H

#include <algorithm>
#include <gtest/gtest.h>
#include <string>

#define CREATURE(name)                                                         \
    dandan::core::Card                                                         \
    {                                                                          \
        new dandan::CardData                                                   \
        {                                                                      \
            formatCardName(#name),                                             \
                std::make_unique<dandan::mana::BlueMana>(2),                   \
                dandan::core::CardData::Type::Creature,                        \
                dandan::core::SubType::Fish,                                   \
                dandan::core::CardData::SuperType::None, name##_Abilities(),   \
                dandan::core::Stats{4, 1}, dandan::core::ColorWord::Blue       \
        }                                                                      \
    }

#define LAND(name, subtype, supertype)                                         \
    dandan::Card                                                               \
    {                                                                          \
        new dandan::CardData                                                   \
        {                                                                      \
            formatCardName(#name),                                             \
                std::make_unique<dandan::mana::GenericMana>(0),                \
                dandan::CardData::Type::Land, dandan::core::SubType::subtype,  \
                dandan::CardData::SuperType::supertype, name##_Abilities()     \
        }                                                                      \
    }

#define SPELL(name, cost, type)                                                \
    dandan::Card                                                               \
    {                                                                          \
        new dandan::CardData                                                   \
        {                                                                      \
            formatCardName(#name), cost, dandan::CardData::Type::type,         \
                dandan::core::SubType::None,                                   \
                dandan::core::CardData::SuperType::None, name##_Abilities(),   \
        }                                                                      \
    }

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