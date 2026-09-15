#ifndef DANDAN_KEYWORD_H
#define DANDAN_KEYWORD_H

#include <cassert>
#include <cstdint>

namespace dandan::abilities
{
    enum class Keyword : uint8_t
    {
        Flying,
        Flashback
    };

} // namespace dandan::abilities

#endif
