#include "dandan/core/Card.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/CardData.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/Game.h"
#include "dandan/log.h"
#include <vector>

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

            auto bound_abilities{std::vector<abilities::BoundAbility>{}};
            for (const auto &ability : m_card_data->getAbilities())
            {
                auto *definition{ability.get()};
                auto bound{abilities::BoundAbility{*definition, this}};
                bound_abilities.push_back(bound);
            }
            m_current_abilities = std::move(bound_abilities);
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
        game.replacementManager().unsubscribe(*card);
        game.graveyard().addCard(*card);
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    void Card::replaceText(ColorWord from, ColorWord new_color)
    {
        // change controls island conditions
        for (auto &ability : getCurrentAbilities())
        {
            ability.addTextReplacement({from, new_color});
        }
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)

    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    void Card::replaceText(SubType from, SubType new_basic)
    {
        if (getCurrentSubType() == from)
        {
            setCurrentSubType(new_basic);
        }

        for (auto &ability : getCurrentAbilities())
        {
            ability.addTextReplacement({from, new_basic});
        }
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)
} // namespace dandan::core