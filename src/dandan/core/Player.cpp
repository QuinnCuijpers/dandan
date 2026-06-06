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
} // namespace dandan::core