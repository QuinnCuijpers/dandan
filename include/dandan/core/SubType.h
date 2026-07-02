#ifndef DANDAN_SUBTYPE_H
#define DANDAN_SUBTYPE_H

#include <cstdint>

namespace dandan::core
{
    /** The subtype of the card. For now every card has exactly one subtype.
     * @enum SubType
     */
    enum class SubType : uint8_t
    {
        /// No subtype
        None,
        /// The forest land subtype
        Forest,
        /// The island land subtype
        Island,
        /// The mountain land subtype
        Mountain,
        /// The plains land subtype
        Plains,
        /// The swamp land subtype
        Swamp,
        /// The fish creature subtype for dandan
        Fish,
        Illusion,
        Dragon,
    };
} // namespace dandan::core

#endif