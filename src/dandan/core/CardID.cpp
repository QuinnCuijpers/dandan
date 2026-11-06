#include "dandan/core/CardID.h"
#include <functional>

namespace dandan::core
{
    CardID CardID::getInvalidID()
    {
        return CardID{-1};
    }

    CardID CardID::generate()
    {
        static int current_id{0};
        return CardID{current_id++};
    }

    CardID CardID::fromInt(int card_id)
    {
        return CardID{card_id};
    }

    bool CardID::operator==(const CardID &other) const
    {
        return m_id == other.m_id;
    }

    bool CardID::operator!=(const CardID &other) const
    {
        return m_id != other.m_id;
    }

    bool CardID::operator<(const CardID &other) const
    {
        return m_id < other.m_id;
    }

    int CardID::getID() const
    {
        return m_id;
    }

    CardID::CardID(int next_id) : m_id(next_id)
    {
    }
} // namespace dandan::core

namespace std
{
    std::size_t hash<dandan::core::CardID>::operator()(
        const dandan::core::CardID &card_id) const
    {
        return std::hash<int>()(card_id.getID());
    }
} // namespace std
