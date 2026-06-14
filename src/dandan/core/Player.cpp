#include "dandan/core/Player.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void Player::drawCard(Game &game)
    {
        auto &library{game.library()};
        if (library.getCards().empty())
        {
            std::cout << "library is empty, cannot draw card\n";
            setDrewCardFromEmptyLibrary(true);
            return;
        }
        auto card_id = library.draw();
        auto *card{game.getCardByID(card_id)};
        card->setControllerID(m_player_id);
        m_hand.addCard(*card);
    }

    void Player::playCard(Card &card)
    {
        std::cout << "Player is playing card " << card.getData().getName()
                  << " with ID " << card.getID().getID() << '\n';
        m_battlefield.addCard(card);
    }

    void Player::discardCard(const Card &card, Game &game)
    {
        std::cout << "Player is discarding card " << card.getData().getName()
                  << '\n';
        m_hand.discardCard(card.getID(), game);
    }

    void Player::sacrificeCard(Card &card, Game &game)
    {
        std::cout << "Player is sacrificing card with ID "
                  << card.getID().getID() << '\n';
        m_battlefield.sacrificeCard(card, game);
    }
} // namespace dandan::core