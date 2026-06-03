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

        /** Set the attacking status of the card.
         * @param is_attacking The new attacking status of the card.
         */
        void setAttacking(bool is_attacking)
        {
            m_is_attacking = is_attacking;
        }

        /** Get whether the card is attacking.
         * @return True if the card is attacking, false otherwise.
         */
        [[nodiscard]] bool isAttacking() const
        {
            return m_is_attacking;
        }

        /** Get whether the card is blocked.
         * @return True if the card is blocked, false otherwise.
         */
        [[nodiscard]] bool isBlocked() const
        {
            return m_is_blocked;
        }

        /** Set the blocked status of the card.
         * @param is_blocked The new blocked status of the card.
         */
        void setBlocked(bool is_blocked)
        {
            m_is_blocked = is_blocked;
        }

        /** Set the blocking status of the card.
         * @param is_blocking The new blocking status of the card.
         */
        void setBlocking(bool is_blocking)
        {
            m_blocking = is_blocking;
        }

        /** Get whether the card is blocking.
         * @return True if the card is blocking, false otherwise.
         */
        [[nodiscard]] bool isBlocking() const
        {
            return m_blocking;
        }

        /** Get the power of the card.
         * @return The power of the card.
         */
        [[nodiscard]] int getPower() const
        {
            return m_current_power;
        }

        /** Get the toughness of the card.
         * @return The toughness of the card.
         */
        [[nodiscard]] int getToughness() const
        {
            return m_current_toughness;
        }

        /** Get the damage marked on the card.
         * @return The damage marked on the card.
         */
        [[nodiscard]] int getDamageMarked() const
        {
            return m_marked_damage;
        }

        // TODO: should generate a damage event
        /** Take damage.
         * @param damage The damage to take.
         * @param game The game instance.
         */
        void takeDamage(int damage, [[maybe_unused]] Game &game)
        {
            m_marked_damage += damage;
        }

        /** Destroy the card.
         * @param game The game instance.
         */
        void destroy(Game &game);

        // TODO: check this thoroughly
        /** Reset the state of the card.
         */
        void resetState()
        {
            m_summoning_sick = true;
            m_is_attacking = false;
            m_is_blocked = false;
            m_blocking = false;
            if (getData().getStats().has_value())
            {
                auto stats = getData().getStats().value();
                m_current_power = stats.power;
                m_current_toughness = stats.toughness;
            }
            m_marked_damage = 0;
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
                        << ", tapped: " << card.m_tapped << ", data: nullptr}"
                        << ", summoning sick: " << card.m_summoning_sick << '}';
                return ostream;
            }
            ostream << "Card{ID: " << card.m_card_id.getID()
                    << ", controller ID: " << card.m_controller_id.id()
                    << ", tapped: " << card.m_tapped
                    << ", summoning sick: " << card.m_summoning_sick
                    << ", data: " << *card.m_card_data << '}';
            return ostream;
        }

    private:
        CardID m_card_id;
        PlayerID m_controller_id;
        bool m_tapped{false};
        Zone m_zone{Zone::LIBRARY};

        bool m_summoning_sick{true};
        bool m_is_attacking{false};
        bool m_is_blocked{false};
        bool m_blocking{false};

        int m_current_power{};
        int m_current_toughness{};
        int m_marked_damage{};

        // static pointer to card data, as the data is shared among all
        // instances of the same card, and we want to avoid copying it for each
        // instance
        CardData *m_card_data;

        void setCurrentPower(int power)
        {
            m_current_power = power;
        }

        void setCurrentToughness(int toughness)
        {
            m_current_toughness = toughness;
        }
    };
} // namespace dandan::core

#endif
