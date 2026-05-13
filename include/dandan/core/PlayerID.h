#ifndef DANDAN_PLAYERID_H
#define DANDAN_PLAYERID_H

#include "dandan/core/constants.h"
#include <stdexcept>

namespace dandan::core
{
    class PlayerID
    {
    public:
        static PlayerID generate()
        {
            static int next_id{};
            if (next_id >= AMOUNT_PLAYERS)
            {
                throw std::runtime_error("Exceeded maximum number of players, "
                                         "cannot generate new PlayerID");
            }
            return PlayerID{next_id++};
        }

        static PlayerID getInvalidID()
        {
            return PlayerID{-1};
        }

        [[nodiscard]] int id() const
        {
            return m_id;
        }

    private:
        int m_id{0};

        explicit PlayerID(int player_id) : m_id(player_id)
        {
            if (player_id >= AMOUNT_PLAYERS)
            {
                throw std::runtime_error(
                    "Player ID exceeds maximum number of players");
            }
        }
    };

} // namespace dandan::core

#endif