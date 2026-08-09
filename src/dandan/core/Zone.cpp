#include "dandan/core/Zone.h"

namespace dandan::core
{
    std::string zoneToString(Zone zone)
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

    std::ostream &operator<<(std::ostream &ostream, Zone zone)
    {
        ostream << zoneToString(zone);
        return ostream;
    }
} // namespace dandan::core
