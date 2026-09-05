#ifndef DANDAN_TESTS_COMMON_H
#define DANDAN_TESTS_COMMON_H

#include "CreatureDefinitions.h"
#include "dandan/core/CardData.h"
#include "dandan/core/CardTypes.h"
#include "dandan/dandan.h"
#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaPrice.h"
#include "dandan/mana/ManaType.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

constexpr int TEST_DECK_SIZE{20};

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

inline std::string formatCardName(std::string_view name)
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

inline std::unique_ptr<dandan::CardData> create_spell_data(
    std::string_view name, dandan::ManaPrice cost, dandan::core::Type type,
    std::vector<std::unique_ptr<dandan::IAbility>> abilities)
{

    return std::make_unique<dandan::CardData>(
        dandan::core::CardData{formatCardName(name),
                               std::move(cost),
                               type,
                               {dandan::core::SubType::None},
                               dandan::core::SuperType::None,
                               std::move(abilities),
                               std::nullopt,
                               dandan::core::ColorWord::Blue});
}

inline std::unique_ptr<dandan::CardData> create_creature_data(
    std::string_view name)
{
    return std::make_unique<dandan::CardData>(
        dandan::core::CardData{formatCardName(name),
                               dandan::mana::ManaPrice{dandan::mana::ManaBag{
                                   {dandan::mana::ManaType::BLUE, 2}}},
                               dandan::core::Type::Creature,
                               {dandan::core::SubType::Fish},
                               dandan::core::SuperType::None,
                               Dandan_Abilities(),
                               dandan::core::Stats{4, 1},
                               dandan::core::ColorWord::Blue});
}

inline std::unique_ptr<dandan::CardData> create_land_data(
    std::string_view name, dandan::core::SuperType supertype,
    dandan::core::SubType subtype,
    std::vector<std::unique_ptr<dandan::IAbility>> abilities)
{
    return std::make_unique<dandan::CardData>(
        dandan::core::CardData{formatCardName(name),
                               dandan::mana::ManaPrice{},
                               dandan::core::Type::Land,
                               {subtype},
                               supertype,
                               std::move(abilities),
                               std::nullopt,
                               dandan::core::ColorWord::Colorless});
}
#endif
