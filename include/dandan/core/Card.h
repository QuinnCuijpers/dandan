#ifndef DANDAN_CARD_H
#define DANDAN_CARD_H

#include "CardData.h"
#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/Zone.h"

#ifdef DANDAN_SERIALIZE
#include <string_view>
#endif

namespace dandan::core
{

    class Card
    {
    public:
#ifdef DANDAN_SERIALIZE
        explicit Card(std::string_view card_name,
                      PlayerID controller_id = PlayerID::getInvalidID());

#endif

        explicit Card(CardData *card_data,
                      PlayerID controller_id = PlayerID::getInvalidID());

        [[nodiscard]] const CardID &getID() const
        {
            return m_card_id;
        }
        [[nodiscard]] PlayerID getControllerID() const
        {
            return m_controller_id;
        }

        [[nodiscard]] bool getTapped() const
        {
            return m_tapped;
        }

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        [[nodiscard]] Zone getZone() const
        {
            return m_zone;
        }

        void setZone(Zone zone)
        {
            m_zone = zone;
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
                        << ", controller ID: " << card.m_controller_id.id()
                        << ", tapped: " << card.m_tapped << ", data: nullptr}";
                return ostream;
            }
            ostream << "Card{ID: " << card.m_card_id.getID()
                    << ", controller ID: " << card.m_controller_id.id()
                    << ", tapped: " << card.m_tapped
                    << ", data: " << *card.m_card_data << '}';
            return ostream;
        }

    private:
        CardID m_card_id;
        PlayerID m_controller_id;
        bool m_tapped{false};
        Zone m_zone{Zone::LIBRARY};

        // static pointer to card data, as the data is shared among all
        // instances of the same card, and we want to avoid copying it for each
        // instance
        CardData *m_card_data;
    };
} // namespace dandan::core

#endif