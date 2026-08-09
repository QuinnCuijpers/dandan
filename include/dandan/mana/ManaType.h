#ifndef DANDAN_MANATYPE_H
#define DANDAN_MANATYPE_H

#include <cassert>
#include <cstdint>
#include <string_view>

namespace dandan::mana
{
    enum class ManaType : std::uint8_t
    {
        GENERIC,
        COLORLESS,
        WHITE,
        BLUE,
        BLACK,
        RED,
        GREEN,
    };

    ManaType ManaTypeFromString(std::string_view str);

} // namespace dandan::mana

#endif
