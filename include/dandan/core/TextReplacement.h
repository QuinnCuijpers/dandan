#ifndef DANDAN_TEXTREPLACEMENT_H
#define DANDAN_TEXTREPLACEMENT_H

#include "dandan/core/ColorWord.h"
#include "dandan/core/SubType.h"
#include <variant>

namespace dandan::core
{
    using ReplacementType = std::variant<SubType, ColorWord>;

    struct TextReplacement
    {
        ReplacementType from;
        ReplacementType to;
    };
} // namespace dandan::core

#endif