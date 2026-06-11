#include "dandan/core/Card.h"
#include "dandan/core/Game.h"
#include "dandan/log.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/core/CardDataFactory.h"
#endif

namespace dandan::core
{
#ifdef DANDAN_SERIALIZE
    Card::Card(std::string_view card_name, PlayerID controller_id)
        : m_card_id(CardID::generate()), m_controller_id(controller_id),
          m_card_data(&CardDataFactory::createCardData(card_name))
    {
        DLOGI << "Creating card: " << card_name
              << " with ID: " << m_card_id.getID() << '\n';
        if (m_card_data != nullptr)
        {
            auto stats = m_card_data->getStats();
            if (stats.has_value())
            {
                setCurrentPower(stats->power);
                setCurrentToughness(stats->toughness);
            }
            setCurrentSubType(m_card_data->getSubType());
        }
    }
#endif

    Card::Card(CardData *card_data, PlayerID controller_id)
        : m_card_id(CardID::generate()), m_controller_id(controller_id),
          m_card_data(card_data)
    {
        DLOGI << "Creating card: " << card_data->getName()
              << " with ID: " << m_card_id.getID() << '\n';
        if (m_card_data != nullptr)
        {
            auto stats = m_card_data->getStats();
            if (stats.has_value())
            {
                setCurrentPower(stats->power);
                setCurrentToughness(stats->toughness);
            }
            setCurrentSubType(m_card_data->getSubType());
        }
    }

    void Card::destroy([[maybe_unused]] Game &game) const
    {
        std::cout << "Destroying card " << getData().getName() << '\n';
        auto *card{game.getCardByID(getID())};
        auto &player{game.getPlayer(card->getControllerID())};
        game.moveCardFromZone(player, *card);
        // remove from managers
        game.eventManager().unsubscribe(*card);
        game.conditionManager().removeCardConditions(card->getID());
        game.preventionManager().unsubscribe(card->getID());
        game.graveyard().addCard(*card);
    }
} // namespace dandan::core