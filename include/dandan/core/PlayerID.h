#ifndef DANDAN_PLAYERID_H
#define DANDAN_PLAYERID_H

#include "dandan/core/Constants.h"
#include <stdexcept>

namespace dandan::core
{
    class PlayerID
    {
    public:
        static int next_id;
        static PlayerID generate()
        {
            if (next_id >= AMOUNT_PLAYERS)
            {
                throw std::runtime_error("Exceeded maximum number of players, "
                                         "cannot generate new PlayerID");
            }
            return PlayerID{next_id++};
        }

        static void reset()
        {
            next_id = 0;
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
        int m_id{};
        explicit PlayerID(int next_id) : m_id(next_id)
        {
        }
    };

} // namespace dandan::core

#endif