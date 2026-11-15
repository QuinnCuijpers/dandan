#ifndef DANDAN_IMINDBENABLE_H
#define DANDAN_IMINDBENABLE_H

#include "dandan/core/CardTypes.h"
#include "dandan/core/ColorWord.h"

namespace dandan::core
{
    /** @brief An interface for objects affected by text-changing effects.
     * @class IMindBendable
     */
    class IMindBendable
    {
    public:
        IMindBendable() = default;
        IMindBendable(const IMindBendable &) = delete;
        IMindBendable(IMindBendable &&) = delete;
        IMindBendable &operator=(const IMindBendable &) = delete;
        IMindBendable &operator=(IMindBendable &&) = delete;
        virtual ~IMindBendable() = default;

        // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        /** Replaces every instance of a color word.
         * @param from The color word to replace.
         * @param new_color The replacement color word.
         */
        virtual void replaceColorWord(ColorWord from, ColorWord new_color);

        /** Replaces every instance of a basic land subtype.
         * @param from The subtype to replace.
         * @param new_basic The replacement subtype.
         */
        virtual void replaceBasicWord(SubType from, SubType new_basic);
        // NOLINTEND(bugprone-easily-swappable-parameters)
    };
} // namespace dandan::core

#endif