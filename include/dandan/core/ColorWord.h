#ifndef DANDAN_COLORWORD_H
#define DANDAN_COLORWORD_H

#include <cstdint>
namespace dandan::core
{
    enum class ColorWord : uint8_t
    {
        White,
        Blue,
        Black,
        Red,
        Green,
        Colorless
    };
} // namespace dandan::core

#endif