#ifndef DANDAN_ZONE_H
#define DANDAN_ZONE_H

#include <cstdint>
#include <string>

namespace dandan::core
{
    enum class Zone : uint8_t
    {
        LIBRARY,
        HAND,
        BATTLEFIELD,
        GRAVEYARD,
        EXILE,
        STACK
    };

    std::string zoneToString(Zone zone);

    std::ostream &operator<<(std::ostream &ostream, Zone zone);

} // namespace dandan::core

#endif // DANDAN_ZONE_H
