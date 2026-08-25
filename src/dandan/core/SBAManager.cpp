#include "dandan/core/SBAManager.h"
#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include "dandan/core/engine/ConditionManager.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/DestroyEffect.h"
#include "dandan/effects/one_shot/LoseGameEffect.h"
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace dandan::core
{
    // TODO: these should all be pushed onto an effect bus, but for now just
    // resolve them immediately inline
    void SBAManager::checkSBAs(ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        // 704.5a If a player has 0 or less life, that player loses the game.
        for (const auto &player : game.getPlayers())
        {
            if (player.getLifeTotal() <= 0)
            {
                std::cout << player.getName()
                          << " has 0 or less life and loses the game.\n";
                effects::EffectContext context{};
                auto lose_effect{std::make_unique<effects::LoseGameEffect>(
                    player.getID(), context)};
                auto final_effect{
                    game.replacementManager().applyReplacementEffects(
                        *lose_effect, exec_ctx)};
                static_cast<void>(final_effect->apply(exec_ctx));
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
                effects::EffectContext context{};
                auto lose_effect{std::make_unique<effects::LoseGameEffect>(
                    player.getID(), context)};
                auto final_effect{
                    game.replacementManager().applyReplacementEffects(
                        *lose_effect, exec_ctx)};
                static_cast<void>(final_effect->apply(exec_ctx));
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
                auto *card{card_registry[card_id]};
                if (card->getToughness() > 0 &&
                    card->getDamageMarked() >= card->getToughness())
                {
                    std::cout << "Creature " << card->getData().name
                              << " with ID " << card->getID().getID()
                              << " has been dealt lethal damage and is "
                                 "destroyed.\n";
                    effects::EffectContext context{};
                    auto destroy_effect{
                        std::make_unique<effects::DestroyEffect>(*card,
                                                                 context)};
                    auto final_effect{
                        game.replacementManager().applyReplacementEffects(
                            *destroy_effect, exec_ctx)};
                    static_cast<void>(final_effect->apply(exec_ctx));
                }
            }
        }

        // check state triggers
        // copy the current triggers so we dont segfault if a trigger causes an
        // effect that removes trigger records
        std::unordered_map<CardID, std::vector<TriggeredRecord>>
            copied_records{};
        const auto &current_records{
            game.conditionManager().getTriggerRecords()};
        std::copy(current_records.begin(), current_records.end(),
                  std::inserter(copied_records, copied_records.begin()));

        for (const auto &[card_id, triggered_records] : copied_records)
        {
            for (const auto &triggered_record : triggered_records)
            {
                if (triggered_record.satisfied)
                {
                    std::cout << "Triggering state triggered ability on card "
                              << card_id.getID() << '\n';
                    PlayerID controller_id{
                        card_registry[card_id]->getControllerID()};
                    abilities::AbilityContext context{card_id, controller_id};
                    auto final_effect{
                        game.replacementManager().applyReplacementEffects(
                            *triggered_record.bound_ability->createEffect(
                                exec_ctx),
                            exec_ctx)};
                    static_cast<void>(final_effect->apply(exec_ctx));
                }
            }
        }
    }
} // namespace dandan::core
