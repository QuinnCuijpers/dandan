#include "dandan/core/Card.h"
#include "dandan/log.h"

#include "dandan/core/CardDataFactory.h"

namespace dandan::core
{

    Card::Card(std::string_view card_name, PlayerID controller_id)
        : m_card_id(CardID::generate()), m_controller_id(controller_id),
          m_card_data(&CardDataFactory::createCardData(card_name))
    {
        DLOGI << "Creating card: " << card_name
              << " with ID: " << m_card_id.getID() << '\n';
    }

    Card::Card(CardData *card_data, PlayerID controller_id)
        : m_card_id(CardID::generate()), m_controller_id(controller_id),
          m_card_data(card_data)
    {
        DLOGI << "Creating card: " << card_data->getName()
              << " with ID: " << m_card_id.getID() << '\n';
    }
} // namespace dandan::core