#include "dandan/core/Player.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    // TODO: does this need to take library?
    void Player::drawCard(Library &library, Game &game)
    {

        {
            if (library.getCards().empty())
            {
                std::cout << "library is empty, cannot draw card\n";
                return;
            }
            auto card_id = library.draw();
            m_hand.addCard(*game.getCardByID(card_id));
        };
    }
} // namespace dandan::core