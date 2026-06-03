#include "dandan/core/SBAManager.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    // TODO: these should all be pushed onto an effect bus, but for now just
    // resolve them immediately inline
    void SBAManager::checkSBAs(Game &game)
    {
        // 704.5a If a player has 0 or less life, that player loses the game.
        for (const auto &player : game.getPlayers())
        {
            if (player.getLifeTotal() <= 0)
            {
                std::cout << player.getName()
                          << " has 0 or less life and loses the game.\n";
            }
        }

        // 704.5b If a player attempted to draw a card from a library with no
        // cards in it since the last time state-based actions were checked,
        // that player loses the game.
        for (const auto &player : game.getPlayers())
        {
            if (player.drewCardFromEmptyLibrary())
            {
                std::cout << player.getName()
                          << " attempted to draw from an empty library and "
                             "loses the game.\n";
            }
        }

        // 704.5g If a creature has toughness greater than 0, it has damage
        // marked on it, and the total damage
        // marked on it is greater than or equal to its toughness, that creature
        // has been dealt lethal damage and is destroyed. Regeneration can
        // replace this event.
        for (const auto &player : game.getPlayers())
        {
            for (const auto &card_id : player.battlefield().getCreatures())
            {
                auto *card{game.getCardByID(card_id)};
                if (card->getToughness() > 0 &&
                    card->getDamageMarked() >= card->getToughness())
                {
                    std::cout << "Creature " << card->getData().getName()
                              << " with ID " << card->getID().getID()
                              << " has been dealt lethal damage and is "
                                 "destroyed.\n";
                }
            }
        }
    }
} // namespace dandan::core