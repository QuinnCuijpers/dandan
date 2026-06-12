#ifndef DANDAN_JSON_ENUMS_H
#define DANDAN_JSON_ENUMS_H

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

    NLOHMANN_JSON_SERIALIZE_ENUM(CardData::SubType, // NOLINT
                                 {{CardData::SubType::None, "None"},
                                  {CardData::SubType::Island, "Island"},
                                  {CardData::SubType::Swamp, "Swamp"},
                                  {CardData::SubType::Mountain, "Mountain"},
                                  {CardData::SubType::Forest, "Forest"},
                                  {CardData::SubType::Plains, "Plains"},
                                  {CardData::SubType::Fish, "Fish"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(CardData::SuperType, // NOLINT
                                 {{CardData::SuperType::None, "None"},
                                  {CardData::SuperType::Basic, "Basic"}});

    NLOHMANN_JSON_SERIALIZE_ENUM(core::TargetType, // NOLINT
                                 {{core::TargetType::Player, "Player"},
                                  {core::TargetType::Creature, "Creature"},
                                  {core::TargetType::Land, "Land"},
                                  {core::TargetType::Planeswalker,
                                   "Planeswalker"},
                                  {core::TargetType::Card, "Card"},
                                  {core::TargetType::Any, "Any"}});

} // namespace dandan::core

#endif // DANDAN_SERIALIZE
#endif // DANDAN_JSON_ENUMS_H