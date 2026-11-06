#ifndef DANDAN_PLAYERID_H
#define DANDAN_PLAYERID_H

#include "dandan/core/Constants.h"
#include <cstddef>
#include <functional>
#include <stdexcept>

namespace dandan::core
{
    /** @brief A class that represents the ID of a player using an
     * auto-incrementing integer.
     * @class PlayerID
     */
    class PlayerID
    {
    public:
        /// The next ID to be assigned to a player.
        static int next_id;

        /** Generates the next PlayerID.
         * @return The generated PlayerID.
         */
        static PlayerID generate();

        /** Resets the PlayerID generator back to the zero id.
         */
        static void reset();

        /** Gets the invalid PlayerID represented by -1.
         * @return The invalid PlayerID.
         */
        static PlayerID getInvalidID();

        /** Gets the underlying integer for the ID of the player.
         * @return The ID of the player.
         */
        [[nodiscard]] int id() const;

        PlayerID static fromInt(int player_id);

        /** Checks if two PlayerIDs are equal.
         * @param other The other PlayerID to compare with.
         * @return True if the PlayerIDs are equal, false otherwise.
         */
        bool operator==(const PlayerID &other) const;

        /** Checks if two PlayerIDs are not equal.
         * @param other The other PlayerID to compare with.
         * @return True if the PlayerIDs are not equal, false otherwise.
         */
        bool operator!=(const PlayerID &other) const;

    private:
        int m_id{};
        explicit PlayerID(int next_id);
    };

} // namespace dandan::core

namespace std
{
    /** Hashing implementation for CardID */
    template <> struct hash<dandan::core::PlayerID>
    {
        /** Hashes a CardID.
         * @param card_id The CardID to hash.
         * @return The hash value.
         */
        std::size_t operator()(const dandan::core::PlayerID &player_id) const;
    };
} // namespace std
#endif
