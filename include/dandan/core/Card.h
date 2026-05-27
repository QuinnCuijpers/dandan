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

    /** @brief A class representing a card instance in the game.
     * @class Card
     * All variable traits of the card instance are stored in this class,
     * while the static traits of the card are stored in CardData accesible
     * through `getData()`.
     */
    class Card
    {
    public:
#ifdef DANDAN_SERIALIZE
        explicit Card(std::string_view card_name,
                      PlayerID controller_id = PlayerID::getInvalidID());

#endif

        /** Constructor for creating a card instance.
         * @param card_data A pointer to the static card data.
         * @param controller_id The ID of the player who controls the card.
         */
        explicit Card(CardData *card_data,
                      PlayerID controller_id = PlayerID::getInvalidID());

        /** Get the ID of the card.
         * @return The ID of the card.
         */
        [[nodiscard]] const CardID &getID() const
        {
            return m_card_id;
        }
        /** Get the ID of the player who controls the card.
         * @return The ID of the player who controls the card.
         */
        [[nodiscard]] PlayerID getControllerID() const
        {
            return m_controller_id;
        }

        /** Get the tapped status of the card.
         * @return The tapped status of the card.
         */
        [[nodiscard]] bool getTapped() const
        {
            return m_tapped;
        }

        /** Set the tapped status of the card.
         * @param tapped The new tapped status of the card.
         */
        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        /** Get the zone the card is currently in.
         * @return The zone the card is currently in.
         */
        [[nodiscard]] Zone getZone() const
        {
            return m_zone;
        }

        /** Set the zone the card is currently in.
         * @param zone The new zone the card is in.
         */
        void setZone(Zone zone)
        {
            m_zone = zone;
        }

        /** Get the static data of the card.
         * @return A const reference to the static card data.
         */
        [[nodiscard]] const CardData &getData() const
        {
            return *m_card_data;
        }

        /** Set the ID of the player who controls the card.
         * @param new_controller_id The new controller ID.
         */
        void setControllerID(PlayerID new_controller_id)
        {
            m_controller_id = new_controller_id;
        }

        /** Get whether the card has summoning sickness.
         * @return True if the card has summoning sickness, false otherwise.
         */
        [[nodiscard]] bool getSummoningSickness() const
        {
            return m_summoning_sick;
        }

        /** Set the state of summoning sickness.
         * @param sickness the boolean value to set the summoning sickness to
         */
        void setSummoningSickness(bool sickness)

        {
            m_summoning_sick = sickness;
        }

        /** Output the card to an ostream.
         * @param ostream The ostream to output the card to.
         * @param card The card to output.
         * @return The ostream.
         */
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
        bool m_summoning_sick{true};

        // static pointer to card data, as the data is shared among all
        // instances of the same card, and we want to avoid copying it for each
        // instance
        CardData *m_card_data;
    };
} // namespace dandan::core

#endif
