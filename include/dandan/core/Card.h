#ifndef DANDAN_CARD_H
#define DANDAN_CARD_H

#include "CardData.h"
#include "CardDataFactory.h"
#include <string_view>

namespace dandan::core
{
    using PlayerID = int;

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

    class Card
    {
    public:
        explicit Card(std::string_view card_name, PlayerID controller_id = -1)
            : m_card_id(CardID::generate()), m_controller_id(controller_id),
              m_card_data(&CardDataFactory::createCardData(card_name))
        {
        }

        explicit Card(CardData *card_data, PlayerID controller_id = -1)
            : m_card_id(CardID::generate()), m_controller_id(controller_id),
              m_card_data(card_data)
        {
        }

        [[nodiscard]] const CardID &getID() const
        {
            return m_card_id;
        }
        [[nodiscard]] PlayerID getControllerID() const
        {
            return m_controller_id;
        }

        [[nodiscard]] const CardData &getData() const
        {
            return *m_card_data;
        }

        void setControllerID(PlayerID new_controller_id)
        {
            m_controller_id = new_controller_id;
        }

        friend std::ostream &operator<<(std::ostream &ostream, const Card &card)
        {
            if (card.m_card_data == nullptr)
            {
                ostream << "Card{ID: " << card.m_card_id.getID()
                        << ", controller ID: " << card.m_controller_id
                        << ", data: nullptr}";
                return ostream;
            }
            ostream << "Card{ID: " << card.m_card_id.getID()
                    << ", controller ID: " << card.m_controller_id
                    << ", data: " << *card.m_card_data << '}';
            return ostream;
        }

        // Other methods to interact with the card instance
    private:
        CardID m_card_id;
        PlayerID m_controller_id;
        // static pointer to card data, as the data is shared among all
        // instances of the same card, and we want to avoid copying it for each
        // instance
        CardData *m_card_data;
    };
} // namespace dandan::core

#endif