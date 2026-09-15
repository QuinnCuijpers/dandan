#include "dandan/core/CastContext.h"
#include "dandan/abilities/keywords/FlashbackAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/GameState.h"
#include "dandan/core/PriorityManager.h"
#include "dandan/core/actions/PlayCardAction.h"

namespace dandan::core
{
    CastContext CastContext::resolveCast(const CastRequest &req,
                                         ExecutionContext exec_ctx)
    {
        auto cards = exec_ctx.cards.get();
        auto priority_manager = exec_ctx.priority_manager.get();
        auto &game = exec_ctx.state.get();

        auto *card{cards[req.card_id]};

        auto zone = Zone::HAND;
        auto cost = card->getData().mana_cost;

        switch (req.mode)
        {
        case CastMode::Normal:
        {
            if (card->getControllerID() !=
                priority_manager.getPlayerWithPriority())
            {
                std::cout << "Card_id: " << req.card_id << '\n';
                throw std::runtime_error(
                    "Only player with priority can play cards, card is "
                    "controlled "
                    "by "
                    "player " +
                    game.getPlayer(card->getControllerID()).getName());
            }

            if (card->getZone() != Zone::HAND)
            {
                throw std::runtime_error(
                    "Card must be in hand to be played instead of in " +
                    zoneToString(card->getZone()));
            }

            break;
        }
        case CastMode::Flashback:
        {
            if (card->getZone() != Zone::GRAVEYARD)
            {
                throw std::runtime_error("Card must be in graveyard to be "
                                         "played via flashback instead of in " +
                                         zoneToString(card->getZone()));
            }

            const auto *flash_back{
                card->getAbility<abilities::FlashbackAbility>()};

            if (flash_back == nullptr)
            {
                throw std::runtime_error("Card must have a flashback ability "
                                         "to cast with flashback");
            }

            cost = flash_back->getCost();
            // TODO: impl a check for flashback;
            // auto iter = std::find_if(abilities.begin(), abilities.end(),
            //                          []() { return true; });
            // TODO: impl a way to find the flashback ability
            // flashBackAbility();
            zone = Zone::GRAVEYARD;
            break;
        }
        }

        return {req.card_id, zone, req.mode, cost};
    }
} // namespace dandan::core
