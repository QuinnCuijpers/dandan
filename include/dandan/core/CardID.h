#ifndef DANDAN_CORE_CARDID_H
#define DANDAN_CORE_CARDID_H

#include <cstddef>
#include <functional>

namespace dandan::core
{
    class CardID
    {
    public:
        static CardID getInvalidID()
        {
            return CardID{-1};
        }

        static CardID generate()
        {
            static int current_id{0};
            return CardID{current_id++};
        }
        bool operator==(const CardID &other) const
        {
            return m_id == other.m_id;
        }

        [[nodiscard]] int getID() const
        {
            return m_id;
        }

    private:
        int m_id{0};
        explicit CardID(int next_id) : m_id(next_id)
        {
        }
    };
} // namespace dandan::core

namespace std
{
    template <> struct hash<dandan::core::CardID>
    {
        std::size_t operator()(const dandan::core::CardID &card_id) const
        {
            return std::hash<int>()(card_id.getID());
        }
    };
} // namespace std

#endif // DANDAN_CORE_CARDID_H
