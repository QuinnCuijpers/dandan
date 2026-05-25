#ifndef DANDAN_CORE_CARDID_H
#define DANDAN_CORE_CARDID_H

#include <cstddef>
#include <functional>

namespace dandan::core
{
    /** @brief A unique identifier for a card. Created through a static counter to
     * ensure uniqueness.
     * @class CardID
     */
    class CardID
    {
    public:
        /** Gets an invalid CardID.
         * @return An invalid CardID.
         */
        static CardID getInvalidID()
        {
            return CardID{-1};
        }

        /** Generates the next unique CardID.
         * @return The next unique CardID.
         */
        static CardID generate()
        {
            static int current_id{0};
            return CardID{current_id++};
        }

        /** Creates a CardID from an integer. Use with caution as this can lead
         * to collisions.
         * @param card_id The integer ID to create the CardID from.
         * @return A new CardID.
         * @note As this can lead to collisions, use it with caution.
         */
        static CardID fromInt(int card_id)
        {
            return CardID{card_id};
        }

        /** Checks if two CardIDs are equal.
         * @param other The other CardID to compare with.
         * @return True if the CardIDs are equal, false otherwise.
         */
        bool operator==(const CardID &other) const
        {
            return m_id == other.m_id;
        }

        /** Gets the integer ID of the card.
         * @return The integer ID of the card.
         */
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
    /** Hashing implementation for CardID */
    template <> struct hash<dandan::core::CardID>
    {
        /** Hashes a CardID.
         * @param card_id The CardID to hash.
         * @return The hash value.
         */
        std::size_t operator()(const dandan::core::CardID &card_id) const
        {
            return std::hash<int>()(card_id.getID());
        }
    };
} // namespace std

#endif // DANDAN_CORE_CARDID_H
