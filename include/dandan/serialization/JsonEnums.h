#ifndef DANDAN_JSON_ENUMS_H
#define DANDAN_JSON_ENUMS_H

#ifdef DANDAN_SERIALIZE
#include "dandan/core/CardData.h"
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

} // namespace dandan::core

#endif

#endif // DANDAN_JSON_ENUMS_H