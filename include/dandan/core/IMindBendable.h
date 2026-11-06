#ifndef DANDAN_IMINDBENABLE_H
#define DANDAN_IMINDBENABLE_H

#include "dandan/core/CardTypes.h"
#include "dandan/core/ColorWord.h"

namespace dandan::core
{
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
        virtual void replaceColorWord(ColorWord from, ColorWord new_color);

        virtual void replaceBasicWord(SubType from, SubType new_basic);
        // NOLINTEND(bugprone-easily-swappable-parameters)
    };
} // namespace dandan::core

#endif