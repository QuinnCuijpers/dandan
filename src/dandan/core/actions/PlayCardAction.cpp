#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/core/Zone.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/ETBEffect.h"
#include "dandan/effects/one_shot/PlayCardEffect.h"

namespace dandan::core
{

    PlayCardAction::PlayCardAction(CardID card_id) : m_card_id{card_id}
    {
    }

    [[nodiscard]] CardID PlayCardAction::getCardID() const
    {
        return m_card_id;
    }

    std::unique_ptr<effects::IOneShotEffect> PlayCardAction::createEffect(
        core::ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};
        auto &prevention_manager{exec_ctx.prevention_manager.get()};
        auto &priority_manager{exec_ctx.priority_manager.get()};
        auto &replacement_manager{exec_ctx.replacement_manager.get()};
        auto &event_manager{exec_ctx.event_manager.get()};
        auto &condition_manager{exec_ctx.condition_manager.get()};

        auto *card{card_registry[m_card_id]};

        // TODO: flashback will break this, but for now itll be fine
        if (card->getZone() != Zone::HAND)
        {
            throw std::runtime_error(
                "Card must be in hand to be played instead of in " +
                zoneToString(card->getZone()));
        }

        if (card->getControllerID() != priority_manager.getPlayerWithPriority())
        {
            throw std::runtime_error(
                "Only player with priority can play cards, card is controlled "
                "by "
                "player " +
                game.getPlayer(card->getControllerID()).getName());
        }

        const auto &data = card->getData();

        std::cout << "Playing card: " << data.name << '\n';

        for (auto &ability : card->getCurrentAbilities())
        {
            event_manager.subscribe(ability);

            replacement_manager.subscribe(ability);

            prevention_manager.subscribe(ability);

            condition_manager.addStateTriggeredAbility(&ability);
        }

        effects::EffectContext context{card->getControllerID()};

        // lands dont use the stack and thus immediately enter
        switch (data.type)
        {
        case Type::Land:
            return std::make_unique<effects::ETBEffect>(*card, context);

        case Type::Creature:
        case Type::Sorcery:
        case Type::Instant:
            return std::make_unique<effects::PlayCardEffect>(*card, context);

        default:
            throw std::runtime_error(
                "Only land/creature cards can be played for now");
        }
    }
} // namespace dandan::core
