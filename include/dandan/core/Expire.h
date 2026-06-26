#ifndef DANDAN_EXPIRE_H
#define DANDAN_EXPIRE_H

#include <cstdint>

namespace dandan::core
{
    enum class ExpireTime : std::uint8_t
    {
        EnfOfTurn,
        None
    };
} // namespace dandan::core

#endif