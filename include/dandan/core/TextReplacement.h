#ifndef DANDAN_TEXTREPLACEMENT_H
#define DANDAN_TEXTREPLACEMENT_H

#include "dandan/core/CardTypes.h"
#include "dandan/core/ColorWord.h"
#include <variant>

namespace dandan::core
{
    using ReplacementType = std::variant<SubType, ColorWord>;

    /** @brief Describes replacing one word with another.
     * @struct TextReplacement
     */
    struct TextReplacement
    {
        /// The word to replace.
        ReplacementType from;
        /// The word to replace it with.
        ReplacementType to;
    };
} // namespace dandan::core

#endif
