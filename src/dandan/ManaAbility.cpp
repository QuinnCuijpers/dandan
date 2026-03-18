#include "dandan/ManaAbility.h"

NLOHMANN_JSON_SERIALIZE_ENUM(ManaAbility::ManaType, {{ManaAbility::ManaType::COLORLESS, "Colorless"},
                                                     {ManaAbility::ManaType::WHITE, "White"},
                                                     {ManaAbility::ManaType::BLUE, "Blue"},
                                                     {ManaAbility::ManaType::BLACK, "Black"},
                                                     {ManaAbility::ManaType::RED, "Red"},
                                                     {ManaAbility::ManaType::GREEN, "Green"}})
