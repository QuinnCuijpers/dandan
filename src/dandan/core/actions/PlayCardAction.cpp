#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/abilities/StateTriggeredAbility.h"
#include "dandan/abilities/StaticAbility.h"
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
        game.eventManager().subscribe(*card);

        for (const auto &ability : card->getData().getAbilities())
        {
            if (const auto *static_ability =
                    dynamic_cast<const abilities::StaticAbility *>(
                        ability.get()))
            {
                std::cout << "Subscribing static ability to a manager\n";
                if (static_ability->getType() ==
                    abilities::StaticAbility::Type::Replacement)
                {
                    const auto *replacement_effect =
                        dynamic_cast<const effects::IReplacementEffect *>(
                            static_ability->getEffect());
                    std::cout << "Subscribing replacement ability to "
                                 "replacement manager\n";
                    game.replacementManager().subscribe(replacement_effect);
                }
                else if (static_ability->getType() ==
                         abilities::StaticAbility::Type::Prevention)
                {
                    const auto *prevention_effect_ptr =
                        dynamic_cast<const effects::IPreventionEffect *>(
                            static_ability->getEffect());
                    if (prevention_effect_ptr == nullptr)
                    {
                        throw std::runtime_error(
                            "Static ability marked as prevention did not "
                            "store a prevention effect");
                    }
                    std::cout << "Subscribing prevention ability to "
                                 "prevention manager\n";
                    game.preventionManager().subscribe(
                        card->getID(), prevention_effect_ptr->clone());
                }
            }
            else if (auto *state_triggered_ability =
                         dynamic_cast<abilities::StateTriggeredAbility *>(
                             ability.get()))
            {
                game.conditionManager().addStateTriggeredAbility(
                    card->getID(), state_triggered_ability);
            }
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