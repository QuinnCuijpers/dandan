#include "dandan/core/GameState.h"

namespace dandan::core
{
    void GameState::moveCardFromZone(Player &player, const Card &card)
    {
        std::cout << "Removing " << card.getID().getID()
                  << " from zone: " << card.getZone() << '\n';
        switch (card.getZone())
        {
        case Zone::HAND:
            player.hand().removeCard(card);
            break;
        case Zone::LIBRARY:
            library().removeCard(card);
            break;
        case Zone::BATTLEFIELD:
            player.battlefield().removeCard(card);
            break;
        case Zone::GRAVEYARD:
            graveyard().removeCard(card);
            break;
        case Zone::EXILE:
        case Zone::STACK:
            // while it is called a stack and it does have FILO properties cards
            // can be removed at any level
            stack().removeObject(card.getID());
            break;
        }
    }

    void GameState::moveCardToZone(Card &card, Player &player, Zone zone)
    {
        switch (zone)
        {
        case Zone::LIBRARY:
            m_library.addCardTop(card);
            break;
        case Zone::HAND:
            player.hand().addCard(card);
            break;
        case Zone::BATTLEFIELD:
            player.battlefield().addCard(card);
            break;
        case Zone::GRAVEYARD:
            m_graveyard.addCard(card);
            break;
        case Zone::EXILE:
            m_exile.addCard(card);
            break;
        case Zone::STACK:
            m_stack.push(card.getID());
            break;
        }
    }
} // namespace dandan::core
