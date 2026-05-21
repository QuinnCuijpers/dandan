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

    inline std::string zoneToString(Zone zone)
    {
        switch (zone)
        {
        case Zone::LIBRARY:
            return "Library";
        case Zone::HAND:
            return "Hand";
        case Zone::BATTLEFIELD:
            return "Battlefield";
        case Zone::GRAVEYARD:
            return "Graveyard";
        case Zone::EXILE:
            return "Exile";
        case Zone::STACK:
            return "Stack";
        default:
            return "Unknown Zone";
        }
    }

    inline std::ostream &operator<<(std::ostream &ostream, Zone zone)
    {
        ostream << zoneToString(zone);
        return ostream;
    }

} // namespace dandan::core

#endif // DANDAN_ZONE_H