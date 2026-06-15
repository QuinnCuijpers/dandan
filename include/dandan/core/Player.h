#ifndef DANDAN_PLAYER_H
#define DANDAN_PLAYER_H

#include "dandan/core/Battlefield.h"
#include "dandan/core/Hand.h"
#include "dandan/mana/Mana.h"
#include <cstddef>

const static int STARTING_HAND_SIZE{7};
const static int STARTING_LIFE_TOTAL{20};

namespace dandan::core
{

    class Game;
    class Card;

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

        /** Sets whether the player drew a card from an empty library this turn.
         * @param drew True if the player drew a card from an empty library this
         * turn, false otherwise. Used to determine if the player should lose
         * the game for drawing from an empty library.
         */
        void setDrewCardFromEmptyLibrary(bool drew)
        {
            m_drew_card_from_empty_library = drew;
        }

        /** Checks if the player drew a card from an empty library this turn.
         * @return True if the player drew a card from an empty library this
         * turn, false otherwise.
         */
        [[nodiscard]] bool drewCardFromEmptyLibrary() const
        {
            return m_drew_card_from_empty_library;
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

        /** Checks if the player has lost the game.
         * @return True if the player has lost the game, false otherwise.
         */
        [[nodiscard]] bool lost() const
        {
            return m_lost_game;
        }

        /** Draws a card from the library.
         * @param game The game instance.
         */
        void drawCard(Game &game);

        void playCard(Card &card);

        void discardCard(const Card &card, Game &game);

        void sacrificeCard(Card &card, Game &game);

        /** Takes damage
         * @param damage The amount of damage to take.
         * @param game The game instance.
         */
        void takeDamage(int damage, [[maybe_unused]] Game &game)
        {
            // TODO: add took damage event
            m_life_total -= damage;
        }

        bool canActivateSomething(Game &game) const;

    private:
        PlayerID m_player_id;
        std::string m_name;
        int m_life_total{STARTING_LIFE_TOTAL};
        Battlefield m_battlefield;
        Hand m_hand;
        mana::Mana m_mana_pool;
        bool m_played_land_this_turn{false};
        bool m_drew_card_from_empty_library{false};
        size_t m_max_hand_size{STARTING_HAND_SIZE};
        // bool m_won_game{false};
        bool m_lost_game{false};
    };
} // namespace dandan::core

#endif
