#ifndef DANDAN_PLAYER_H
#define DANDAN_PLAYER_H

#include "dandan/core/Battlefield.h"
#include "dandan/core/Card.h"
#include "dandan/core/Hand.h"
#include "dandan/core/Library.h"
#include "dandan/mana/Mana.h"
#include <cstddef>

const static int STARTING_HAND_SIZE{7};
const static int STARTING_LIFE_TOTAL{20};

namespace dandan::core
{

    class Game;

    /** @brief The class that represents a player in the game.
     * @class Player
     */
    class Player
    {

    public:
        // TODO: change to have players input names through gui
        explicit Player() : m_player_id(PlayerID::generate())
        {
            std::cout << "Constructed player\n";
            std::cout << "Which name do you want to give this player? ";
            std::getline(std::cin, m_name);
        }

        /** Constructs a player with the given name.
         * @param name The name of the player.
         */
        explicit Player(std::string name)
            : m_player_id(PlayerID::generate()), m_name(std::move(name))
        {
            std::cout << "Constructed player with name " << m_name << '\n';
        }

        /** Gets the name of the player.
         * @return a const reference to the name of the player.
         */
        [[nodiscard]] const std::string &getName() const
        {
            return m_name;
        };

        /** Gets the ID of the player.
         * @return a const reference to the ID of the player.
         */
        [[nodiscard]] const PlayerID &getID() const
        {
            return m_player_id;
        }

        /** Gets the life total of the player.
         * @return The life total of the player.
         */
        [[nodiscard]] int getLifeTotal() const
        {
            return m_life_total;
        }

        /** Gets the hand of the player mutably.
         * @return A reference to the hand of the player.
         */
        [[nodiscard]] Hand &hand()
        {
            return m_hand;
        }

        /** Gets the hand of the player immutably.
         * @return A const reference to the hand of the player.
         */
        [[nodiscard]] const Hand &hand() const
        {
            return m_hand;
        }

        /** Sets the hand of the player.
         * @param hand The new hand for the player.
         */
        void setHand(Hand &&hand)
        {
            m_hand = std::move(hand);
        }

        /** Gets the battlefield of the player mutably.
         * @return A reference to the battlefield of the player.
         */
        [[nodiscard]] Battlefield &battlefield()
        {
            return m_battlefield;
        }

        /** Gets the battlefield of the player immutably.
         * @return A const reference to the battlefield of the player.
         */
        [[nodiscard]] const Battlefield &battlefield() const
        {
            return m_battlefield;
        }

        /** Checks if the player has played a land this turn.
         * @return True if the player has played a land this turn, false
         * otherwise.
         */
        [[nodiscard]] bool playedLandThisTurn() const
        {
            return m_played_land_this_turn;
        }

        /** Sets whether the player has played a land this turn.
         * @param played True if the player has played a land this turn, false
         * otherwise.
         */
        void setPlayedLandThisTurn(bool played)
        {
            m_played_land_this_turn = played;
        }

        /** Gets the maximum hand size of the player.
         * @return The maximum hand size of the player.
         */
        [[nodiscard]] size_t maxHandSize() const
        {
            return m_max_hand_size;
        }

        /** Gets the mana pool of the player mutably.
         * @return A reference to the mana pool of the player.
         */
        [[nodiscard]] mana::Mana &manaPool()
        {
            return m_mana_pool;
        }

        /** Gets the mana pool of the player immutably.
         * @return A const reference to the mana pool of the player.
         */
        [[nodiscard]] const mana::Mana &manaPool() const
        {
            return m_mana_pool;
        }

        /** Draws a card from the library.
         * @param library The library to draw from.
         * @param game The game instance.
         */
        void drawCard(Library &library, Game &game);

        /** Plays a card from the player's hand.
         * @param card The card to play.
         */
        void playCard(Card &card)
        {
            std::cout << "Player is playing card " << card.getData().getName()
                      << " with ID " << card.getID().getID() << '\n';
            m_battlefield.addCard(card);
        }

        /** Discards a card from the player's hand.
         * @param card The card to discard.
         */
        void discardCard(Card &card)
        {
            std::cout << "Player is discarding card "
                      << card.getData().getName() << '\n';
            m_hand.discardCard(card);
        }

        /** Takes damage
         * @param damage The amount of damage to take.
         * @param game The game instance.
         */
        void takeDamage(int damage, [[maybe_unused]] Game &game)
        {
            m_life_total -= damage;
            // TODO: death check should be some state based action not checked
            // here
            // TODO: this should notify a damage event
        }

    private:
        PlayerID m_player_id;
        std::string m_name;
        int m_life_total{STARTING_LIFE_TOTAL};
        Battlefield m_battlefield;
        Hand m_hand;
        mana::Mana m_mana_pool;
        bool m_played_land_this_turn{false};
        size_t m_max_hand_size{STARTING_HAND_SIZE};
    };
} // namespace dandan::core

#endif
