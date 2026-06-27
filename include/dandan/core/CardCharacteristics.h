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
        ColorWord color;
        SubType subtype;
        Stats base_stats;
        bool loses_all_abilities;
        std::vector<abilities::IAbility *> additional_abilities;
    };
} // namespace dandan::core

#endif
