#ifndef DANDAN_JSON_ENUMS_H
#define DANDAN_JSON_ENUMS_H

#include "dandan/core/ColorWord.h"
#include "dandan/core/Expire.h"
#include "dandan/core/Keyword.h"
#include "nlohmann/detail/macro_scope.hpp"
#ifdef DANDAN_SERIALIZE
#include "dandan/core/TargetRequirement.h"
#include <nlohmann/json.hpp>

namespace dandan::core
{
    NLOHMANN_JSON_SERIALIZE_ENUM(Type, // NOLINT
                                 {{Type::Land, "Land"},
                                  {Type::Creature, "Creature"},
                                  {Type::Sorcery, "Sorcery"},
                                  {Type::Instant, "Instant"},
                                  {Type::Enchantment, "Enchantment"},
                                  {Type::Artifact, "Artifact"},
                                  {Type::Planeswalker, "Planeswalker"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(SubType, // NOLINT
                                 {{SubType::None, "None"},
                                  {SubType::Island, "Island"},
                                  {SubType::Swamp, "Swamp"},
                                  {SubType::Mountain, "Mountain"},
                                  {SubType::Forest, "Forest"},
                                  {SubType::Plains, "Plains"},
                                  {SubType::Fish, "Fish"},
                                  {SubType::Illusion, "Illusion"},
                                  {SubType::Dragon, "Dragon"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(SuperType, // NOLINT
                                 {{SuperType::None, "None"},
                                  {SuperType::Basic, "Basic"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(TargetType, // NOLINT
                                 {{TargetType::Player, "Player"},
                                  {TargetType::Creature, "Creature"},
                                  {TargetType::Permanent, "Permanent"},
                                  {TargetType::Land, "Land"},
                                  {TargetType::Planeswalker, "Planeswalker"},
                                  {TargetType::Spell, "Spell"},
                                  {TargetType::Card, "Card"},
                                  {TargetType::Any, "Any"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(ExpireTime, // NOLINT
                                 {{ExpireTime::EnfOfTurn, "EndOfTurn"},
                                  {ExpireTime::None, "None"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(Controller, // NOLINT
                                 {{Controller::Any, "Any"},
                                  {Controller::You, "You"},
                                  {Controller::Opponent, "Opponent"}})

    NLOHMANN_JSON_SERIALIZE_ENUM(ColorWord, // NOLINT
                                 {{ColorWord::Black, "Black"},
                                  {ColorWord::Blue, "Blue"},
                                  {ColorWord::Green, "Green"},
                                  {ColorWord::Colorless, "None"},
                                  {ColorWord::Red, "Red"},
                                  {ColorWord::White, "White"}})

    // NOLINTNEXTLINE
    NLOHMANN_JSON_SERIALIZE_ENUM(Keyword, {{Keyword::Flying, "Flying"}})

} // namespace dandan::core

namespace dandan::abilities
{
    NLOHMANN_JSON_SERIALIZE_ENUM( // NOLINT
        StaticAbility::Type,
        {{StaticAbility::Type::CharacteristicDefining,
          "CharacteristicDefining"},
         {StaticAbility::Type::Prevention, "Prevention"},
         {StaticAbility::Type::Replacement, "Replacement"}});
}

#endif // DANDAN_SERIALIZE
#endif // DANDAN_JSON_ENUMS_H
