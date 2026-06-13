
#ifndef DANDAN_STRINGTOCOLORWORD_H
#define DANDAN_STRINGTOCOLORWORD_H

#include "dandan/core/ColorWord.h"
#include <algorithm>
#include <cctype>
#include <string>

namespace dandan::utils
{
    inline core::ColorWord stringToColorWord(const std::string &str)
    {
        std::string lowered{str};
        std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                       [](unsigned char char_)
                       { return static_cast<char>(std::tolower(char_)); });

        if (lowered == "white")
        {
            return core::ColorWord::White;
        }
        if (lowered == "blue")
        {
            return core::ColorWord::Blue;
        }
        if (lowered == "black")
        {
            return core::ColorWord::Black;
        }
        if (lowered == "red")
        {
            return core::ColorWord::Red;
        }

        if (lowered == "green")
        {
            return core::ColorWord::Green;
        }

        return core::ColorWord::None;
    }
} // namespace dandan::utils
#endif