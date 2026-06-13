#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/core/Game.h"
#include "dandan/core/Zone.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/effects/one_shot/PlayCardEffect.h"

namespace dandan::core
{
    std::unique_ptr<effects::IOneShotEffect> PlayCardAction::createEffect(
        core::Game &game)
    {
        auto *card{game.getCardByID(m_card_id)};

        // TODO: flashback will break this, but for now itll be fine
        if (card->getZone() != Zone::HAND)
        {
            throw std::runtime_error(
                "Card must be in hand to be played instead of in " +
                zoneToString(card->getZone()));
        }

        if (card->getControllerID().id() !=
            game.priorityManager().getPlayerWithPriority().id())
        {
            throw std::runtime_error(
                "Only player with priority can play cards, card is controlled "
                "by "
                "player " +
                std::to_string(card->getControllerID().id()));
        }

        const auto &data = card->getData();

        std::cout << "Playing card: " << data.getName() << '\n';

        for (auto &ability : card->getCurrentAbilities())
        {
            game.eventManager().subscribe(ability);

            game.replacementManager().subscribe(ability);

            game.preventionManager().subscribe(ability);

            game.conditionManager().addStateTriggeredAbility(&ability);
        }

        // lands dont use the stack and thus immediately enter
        switch (data.getType())
        {
        case CardData::Type::Land:
            return std::make_unique<effects::ETBEffect>(*card);

        case CardData::Type::Creature:
        case CardData::Type::Sorcery:
        case CardData::Type::Instant:
            std::cout << "Playing card: " << data.getName() << '\n';
            return std::make_unique<effects::PlayCardEffect>(*card);

        default:
            throw std::runtime_error(
                "Only land/creature cards can be played for now");
        }
    }
} // namespace dandan::core