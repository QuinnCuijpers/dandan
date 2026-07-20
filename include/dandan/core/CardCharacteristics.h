#ifndef DANDAN_CARDCHARACTERISTICS_H
#define DANDAN_CARDCHARACTERISTICS_H

#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardData.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/SubType.h"
#include <vector>

namespace dandan::core
{
    struct CardCharacteristics
    {
        ColorWord color{ColorWord::Colorless};
        // could be unordered set, but json requires order preservation
        std::vector<SubType> subtypes;
        Stats base_stats;
        bool loses_all_abilities{};
        std::vector<const abilities::IAbility *> additional_abilities;
    };
} // namespace dandan::core

#endif
