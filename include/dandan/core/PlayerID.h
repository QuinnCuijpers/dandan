#ifndef DANDAN_PLAYERID_H
#define DANDAN_PLAYERID_H

#include "dandan/core/Constants.h"
#include <stdexcept>

namespace dandan::core
{
    /** @brief A class that represents the ID of a player using an auto-incrementing
     * integer.
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
        static PlayerID generate()
        {
            if (next_id >= AMOUNT_PLAYERS)
            {
                throw std::runtime_error("Exceeded maximum number of players, "
                                         "cannot generate new PlayerID");
            }
            return PlayerID{next_id++};
        }

        /** Resets the PlayerID generator back to the zero id.
         */
        static void reset()
        {
            next_id = 0;
        }

        /** Gets the invalid PlayerID represented by -1.
         * @return The invalid PlayerID.
         */
        static PlayerID getInvalidID()
        {
            return PlayerID{-1};
        }

        /** Gets the underlying integer for the ID of the player.
         * @return The ID of the player.
         */
        [[nodiscard]] int id() const
        {
            return m_id;
        }

    private:
        int m_id{};
        explicit PlayerID(int next_id) : m_id(next_id)
        {
        }
    };

} // namespace dandan::core

#endif
