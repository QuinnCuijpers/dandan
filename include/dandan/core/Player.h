#ifndef DANDAN_PLAYER_H
#define DANDAN_PLAYER_H

#include "dandan/core/Battlefield.h"
#include "dandan/core/Deck.h"
#include "dandan/core/Hand.h"
#include "dandan/mana/Mana.h"
#include <cstddef>

const static int STARTING_HAND_SIZE{7};
const static int STARTING_LIFE_TOTAL{20};

namespace dandan::core
{
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

        explicit Player(std::string name)
            : m_player_id(PlayerID::generate()), m_name(std::move(name))
        {
            std::cout << "Constructed player with name " << m_name << '\n';
        }

        [[nodiscard]] const std::string &getName() const
        {
            return m_name;
        };

        [[nodiscard]] Hand &hand()
        {
            return m_hand;
        }

        [[nodiscard]] const Hand &hand() const
        {
            return m_hand;
        }

        void setHand(Hand &&hand)
        {
            m_hand = std::move(hand);
        }

        [[nodiscard]] int getLifeTotal() const
        {
            return m_life_total;
        }

        [[nodiscard]] Battlefield &battlefield()
        {
            return m_battlefield;
        }

        [[nodiscard]] const Battlefield &battlefield() const
        {
            return m_battlefield;
        }

        [[nodiscard]] bool playedLandThisTurn() const
        {
            return m_played_land_this_turn;
        }

        void setPlayedLandThisTurn(bool played)
        {
            m_played_land_this_turn = played;
        }

        [[nodiscard]] size_t maxHandSize() const
        {
            return m_max_hand_size;
        }

        void drawCard(Deck &deck)
        {
            if (deck.getCards().empty())
            {
                std::cout << "Deck is empty, cannot draw card\n";
                return;
            }
            auto card = deck.draw()[0];
            card.setControllerID(m_player_id);
            m_hand.addCards({card});
        }

        void playCard(const Card &card)
        {
            std::cout << "Player is playing card " << card.getData().getName()
                      << " with ID " << card.getID().getID() << '\n';
            m_battlefield.addCard(card);
        }

        void playCard(int index)
        {
            std::cout << "Player is playing card at index " << index << '\n';
            m_battlefield.addCard(m_hand.getCard(index));
        }

        void discardCard(int index)
        {
            std::cout << "Player is discarding card at index " << index << '\n';
            m_hand.discardCard(index);
        }

    private:
        PlayerID m_player_id;
        std::string m_name;
        int m_life_total{STARTING_LIFE_TOTAL};
        Battlefield m_battlefield;
        Hand m_hand;
        mana::ManaMap m_mana_pool;
        bool m_played_land_this_turn{false};
        size_t m_max_hand_size{STARTING_HAND_SIZE};
    };
} // namespace dandan::core

#endif