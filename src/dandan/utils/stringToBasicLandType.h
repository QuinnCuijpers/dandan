#ifndef DANDAN_STRINGTOBASICLANDTYPE_H
#define DANDAN_STRINGTOBASICLANDTYPE_H

#include "dandan/core/SubType.h"
#include <algorithm>
#include <cctype>
#include <string>

namespace dandan::utils
{
    inline core::SubType stringToBasicLandType(const std::string &str)
    {
        std::string lowered{str};
        std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                       [](unsigned char char_)
                       { return static_cast<char>(std::tolower(char_)); });

        if (lowered == "plains")
        {
            return core::SubType::Plains;
        }
        if (lowered == "island")
        {
            return core::SubType::Island;
        }
        if (lowered == "swamp")
        {
            return core::SubType::Swamp;
        }
        if (lowered == "mountain")
        {
            return core::SubType::Mountain;
        }

        if (lowered == "forest")
        {
            return core::SubType::Forest;
        }

        return core::SubType::None;
    }
} // namespace dandan::utils
#endif