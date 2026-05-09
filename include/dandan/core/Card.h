#ifndef DANDAN_CARD_H
#define DANDAN_CARD_H

#include "CardData.h"
#include "CardDataFactory.h"
#include <string_view>

namespace dandan::core
{
    class CardID
    {
    public:
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

    class PLayerID
    {
    public:
        static PLayerID generate()
        {
            static int current_id{0};
            return PLayerID{current_id++};
        }
        bool operator==(const PLayerID &other) const
        {
            return m_id == other.m_id;
        }

        [[nodiscard]] int getId() const
        {
            return m_id;
        }

    private:
        int m_id{0};
        explicit PLayerID(int next_id) : m_id(next_id)
        {
        }
    };

    class Card
    {
    public:
        explicit Card(std::string_view card_name)
            : m_card_id(CardID::generate()),
              m_controller_id(PLayerID::generate()),
              m_card_data(&CardDataFactory::createCardData(card_name))
        {
        }

        explicit Card(CardData *card_data)
            : m_card_id(CardID::generate()),
              m_controller_id(PLayerID::generate()), m_card_data(card_data)
        {
        }

        [[nodiscard]] const CardID &getID() const
        {
            return m_card_id;
        }
        [[nodiscard]] PLayerID getControllerID() const
        {
            return m_controller_id;
        }

        [[nodiscard]] const CardData &getData() const
        {
            return *m_card_data;
        }

        friend std::ostream &operator<<(std::ostream &ostream, const Card &card)
        {
            if (card.m_card_data == nullptr)
            {
                ostream << "Card{ID: " << card.m_card_id.getID()
                        << ", controller ID: " << card.m_controller_id.getId()
                        << ", data: nullptr}";
                return ostream;
            }
            ostream << "Card{ID: " << card.m_card_id.getID()
                    << ", controller ID: " << card.m_controller_id.getId()
                    << ", data: " << *card.m_card_data << '}';
            return ostream;
        }

        // Other methods to interact with the card instance
    private:
        CardID m_card_id;
        PLayerID m_controller_id;
        // static pointer to card data, as the data is shared among all
        // instances of the same card, and we want to avoid copying it for each
        // instance
        CardData *m_card_data;
    };
} // namespace dandan::core

#endif