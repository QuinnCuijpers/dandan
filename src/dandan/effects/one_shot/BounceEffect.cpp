#include "dandan/effects/one_shot/BounceEffect.h"
#include "dandan/core/CardID.h"
#include "dandan/core/GameState.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>
#include <stdexcept>
#include <utility>
#include <variant>

namespace dandan::effects
{
    BounceEffect::BounceEffect(core::Target target, EffectContext context)
        : IOneShotEffect(std::move(context)), m_target(std::move(target))
    {
    }

    std::unique_ptr<IOneShotEffect> BounceEffect::copy() const
    {
        return std::make_unique<BounceEffect>(m_target, getEffectContext());
    }

    std::string BounceEffect::display() const
    {
        return "Return target spell or creature to its owner's hand.";
    }

    BounceEffectDefinition::BounceEffectDefinition(
        core::TargetRequirement target_requirements)
        : m_target_requirements(std::move(target_requirements))
    {
    }

    std::unique_ptr<IOneShotEffect> BounceEffectDefinition::bind(
        const core::ExecutionContext exec_ctx, EffectContext context) const
    {
        if (context.card_id == core::CardID::getInvalidID())
        {
            throw std::runtime_error(
                "tried binding a Bounce Effect without a source card");
        }

        const auto &card_registry{exec_ctx.cards.get()};
        auto source{context.card_id};
        const auto *card{card_registry.get(source)};
        auto choices{card->getTargetChoices(*this)};
        auto choice{choices.at(0)};
        return std::make_unique<BounceEffect>(choice, context);
    }

    std::unique_ptr<IOneShotEffectDefinition> BounceEffectDefinition::clone()
        const
    {
        return std::make_unique<BounceEffectDefinition>(m_target_requirements);
    }

    const core::TargetRequirement *BounceEffectDefinition::
        getTargetRequirement() const
    {
        return &m_target_requirements;
    }

    std::unique_ptr<events::IEvent> BounceEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::CardID>(m_target))
        {
            throw std::runtime_error("Bounce Effect target is not a CardID");
        }
        auto card_id{std::get<core::CardID>(m_target)};
        auto *card{card_registry.get(card_id)};
        auto &controller{game.getPlayer(card->getControllerID())};

        game.moveCardFromZone(controller, *card);
        controller.hand().addCard(*card);
        return nullptr;
    }

} // namespace dandan::effects
