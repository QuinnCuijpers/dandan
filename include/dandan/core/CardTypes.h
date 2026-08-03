#ifndef DANDAN_CARDTYPES_H
#define DANDAN_CARDTYPES_H

#include <cstdint>
#include <string_view>

namespace dandan::core
{
    /** The type of the card. For now every card has exactly one type.
     * @enum Type
     */
    enum class Type : std::uint8_t
    {
        /// A land card
        Land,
        /// A creature card
        Creature,
        /// A sorcery card
        Sorcery,
        /// An instant card
        Instant,
        /// An enchantment card
        Enchantment,
        /// An artifact card
        Artifact,
        /// A planeswalker card
        Planeswalker,
    };

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

    // TODO: expand supertypes
    enum class SuperType : std::uint8_t
    {
        None,
        Basic,
    };

    /** Converts a card type to a string.
     * @param type The card type.
     * @return The string representation of the card type.
     */
    std::string_view TypeToString(Type type);

    /** Converts a card subtype to a string.
     * @param subtype The card subtype.
     * @return The string representation of the card subtype.
     */
    std::string_view SubTypeToString(SubType subtype);

} // namespace dandan::core

#endif
