#include "dandan/core/PlayerID.h"
#include <functional>
#include <stdexcept>
#include <string>

namespace dandan::core
{
    int PlayerID::next_id{};

    PlayerID PlayerID::generate()
    {
        if (next_id >= AMOUNT_PLAYERS)
        {
            throw std::runtime_error("Exceeded maximum number of players, "
                                     "cannot generate new PlayerID");
        }
        return PlayerID{next_id++};
    }

    void PlayerID::reset()
    {
        next_id = 0;
    }

    PlayerID PlayerID::getInvalidID()
    {
        return PlayerID{-1};
    }

    int PlayerID::id() const
    {
        return m_id;
    }

    PlayerID PlayerID::fromInt(int player_id)
    {
        if (player_id < -1 || player_id >= AMOUNT_PLAYERS)
        {
            throw std::runtime_error("Invalid integer for PlayerID: " +
                                     std::to_string(player_id));
        }
        return PlayerID{player_id};
    }

    bool PlayerID::operator==(const PlayerID &other) const
    {
        return m_id == other.m_id;
    }

    bool PlayerID::operator!=(const PlayerID &other) const
    {
        return m_id != other.m_id;
    }

    PlayerID::PlayerID(int next_id) : m_id(next_id)
    {
    }
} // namespace dandan::core

namespace std
{
    std::size_t hash<dandan::core::PlayerID>::operator()(
        const dandan::core::PlayerID &player_id) const
    {
        return std::hash<int>()(player_id.id());
    }
} // namespace std
