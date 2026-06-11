#ifndef DANDAN_SELFSACRIFICEEFFECT_H
#define DANDAN_SELFSACRIFICEEFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <iostream>

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
        explicit SelfSacrificeEffect(core::CardID card_id) : m_card_id(card_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<SelfSacrificeEffect>(m_card_id);
        }

        std::unique_ptr<events::IEvent> apply_impl(
            [[maybe_unused]] core::Game &game) const override
        {
            std::cout << "Resolving SelfSacrificeEffect: Sacrificing the "
                         "source card.\n";
            return nullptr;
        }

    private:
        core::CardID m_card_id;
    };

    class SelfSacrificeEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            return std::make_unique<SelfSacrificeEffect>(
                context.card().value());
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<SelfSacrificeEffectDefinition>();
        }
    };
} // namespace dandan::effects

#endif
