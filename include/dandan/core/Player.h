#ifndef DANDAN_PLAYER_H
#define DANDAN_PLAYER_H

#include "dandan/core/Battlefield.h"
#include "dandan/core/Hand.h"
#include "dandan/mana/Mana.h"

const static int STARTING_HAND_SIZE{7};
const static int STARTING_LIFE_TOTAL{20};

namespace dandan::core
{
    class Player
    {
    public:
        [[nodiscard]] const Hand &getHand() const
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

        [[nodiscard]] const Battlefield &getBattlefield() const
        {
            return m_battlefield;
        }

        void playCard(int index)
        {
            std::cout << "Player is playing card at index " << index << '\n';
            m_battlefield.addCard(m_hand.getCard(index));
        }

    private:
        int m_life_total{STARTING_LIFE_TOTAL};
        Battlefield m_battlefield;
        Hand m_hand;
        mana::ManaMap m_mana_pool;
    };
} // namespace dandan::core

#endif