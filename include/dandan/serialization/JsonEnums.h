#ifndef DANDAN_JSON_ENUMS_H
#define DANDAN_JSON_ENUMS_H

#include "dandan/core/ColorWord.h"
#include "dandan/core/Expire.h"
#include "dandan/core/Keyword.h"
#include "dandan/core/SubType.h"
#include "nlohmann/detail/macro_scope.hpp"
#ifdef DANDAN_SERIALIZE
#include "dandan/core/CardData.h"
#include "dandan/core/TargetRequirement.h"
#include <nlohmann/json.hpp>

namespace dandan::core
{
    NLOHMANN_JSON_SERIALIZE_ENUM(CardData::Type, // NOLINT
                                 {{CardData::Type::Land, "Land"},
                                  {CardData::Type::Creature, "Creature"},
                                  {CardData::Type::Sorcery, "Sorcery"},
                                  {CardData::Type::Instant, "Instant"},
                                  {CardData::Type::Enchantment, "Enchantment"},
                                  {CardData::Type::Artifact, "Artifact"},
                                  {CardData::Type::Planeswalker,
                                   "Planeswalker"}});

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

    NLOHMANN_JSON_SERIALIZE_ENUM(CardData::SuperType, // NOLINT
                                 {{CardData::SuperType::None, "None"},
                                  {CardData::SuperType::Basic, "Basic"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(core::TargetType, // NOLINT
                                 {{core::TargetType::Player, "Player"},
                                  {core::TargetType::Creature, "Creature"},
                                  {core::TargetType::Permanent, "Permanent"},
                                  {core::TargetType::Land, "Land"},
                                  {core::TargetType::Planeswalker,
                                   "Planeswalker"},
                                  {core::TargetType::Spell, "Spell"},
                                  {core::TargetType::Card, "Card"},
                                  {core::TargetType::Any, "Any"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(core::ExpireTime, // NOLINT
                                 {{ExpireTime::EnfOfTurn, "EndOfTurn"},
                                  {ExpireTime::None, "None"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(core::Controller, // NOLINT
                                 {{Controller::Any, "Any"},
                                  {Controller::You, "You"},
                                  {Controller::Opponent, "Opponent"}})

    NLOHMANN_JSON_SERIALIZE_ENUM(ColorWord, // NOLINT
                                 {{ColorWord::Black, "Black"},
                                  {ColorWord::Blue, "Blue"},
                                  {ColorWord::Green, "Green"},
                                  {ColorWord::None, "None"},
                                  {ColorWord::Red, "Red"},
                                  {ColorWord::White, "White"}})

    // NOLINTNEXTLINE
    NLOHMANN_JSON_SERIALIZE_ENUM(Keyword, {{Keyword::Flying, "Flying"}})

} // namespace dandan::core

#endif // DANDAN_SERIALIZE
#endif // DANDAN_JSON_ENUMS_H