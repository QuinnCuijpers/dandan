#ifndef DANDAN_SELFSACRIFICEEFFECT_H
#define DANDAN_SELFSACRIFICEEFFECT_H

#include "dandan/core/Game.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <iostream>
#include <utility>

// should take a card as member variable, but cant rn due to serialization
namespace dandan::effects
{
    /**
     * @brief Represents an effect that sacrifices the underlying card
     *@class SelfSacrificeEffect
     *
     *@implements IOneShotEffect
     */
    class SelfSacrificeEffect : public IOneShotEffect
    {
    public:
        explicit SelfSacrificeEffect(core::CardID card_id,
                                     EffectContext context)
            : IOneShotEffect(std::move(context)), m_card_id(card_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<SelfSacrificeEffect>(m_card_id,
                                                         getEffectContext());
        }

        std::unique_ptr<events::IEvent> apply_impl(
            [[maybe_unused]] core::Game &game) const override
        {
            auto *card{game.getCardByID(m_card_id)};
            card->destroy(game);
            return nullptr;
        }

    private:
        core::CardID m_card_id;
    };

    class SelfSacrificeEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] const core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<SelfSacrificeEffect>(
                context.card_id.value(), context);
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<SelfSacrificeEffectDefinition>();
        }
    };
} // namespace dandan::effects

#endif
