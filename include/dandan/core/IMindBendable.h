#ifndef DANDAN_IMINDBENABLE_H
#define DANDAN_IMINDBENABLE_H

#include "dandan/core/ColorWord.h"
#include "dandan/core/SubType.h"

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
        virtual void replaceColorWord([[maybe_unused]] ColorWord from,
                                      [[maybe_unused]] ColorWord new_color)
        {
        }

        virtual void replaceBasicWord([[maybe_unused]] SubType from,
                                      [[maybe_unused]] SubType new_basic)
        {
        }
        // NOLINTEND(bugprone-easily-swappable-parameters)
    };
} // namespace dandan::core

#endif