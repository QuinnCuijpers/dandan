#ifndef DANDAN_STRINGTOBASICLANDTYPE_H
#define DANDAN_STRINGTOBASICLANDTYPE_H

#include "dandan/core/CardData.h"
#include <algorithm>
#include <cctype>
#include <string>

namespace dandan::utils
{
    inline core::CardData::SubType stringToBasicLandType(const std::string &str)
    {
        std::string lowered{str};
        std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                       [](unsigned char char_)
                       { return static_cast<char>(std::tolower(char_)); });

        if (lowered == "plains")
        {
            return core::CardData::SubType::Plains;
        }
        if (lowered == "island")
        {
            return core::CardData::SubType::Island;
        }
        if (lowered == "swamp")
        {
            return core::CardData::SubType::Swamp;
        }
        if (lowered == "mountain")
        {
            return core::CardData::SubType::Mountain;
        }
        return core::CardData::SubType::Forest;
    }
} // namespace dandan::utils
#endif