#include "dandan/core/Battlefield.h"
#include "dandan/core/Expire.h"
#include "dandan/core/GameState.h"
#include "dandan/effects/one_shot/ChangeCharasticsEffect.h"
#include "dandan/events/IEvent.h"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <variant>

namespace dandan::effects
{
    ChangeCharacteristicsEffect::ChangeCharacteristicsEffect(
        core::Target target, core::CardCharacteristics characteristics,
        EffectContext context)
        : IOneShotEffect(std::move(context)), m_target(std::move(target)),
          m_card_characteristics(std::move(characteristics))
    {
    }

    std::unique_ptr<IOneShotEffect> ChangeCharacteristicsEffect::copy() const
    {
        return std::make_unique<ChangeCharacteristicsEffect>(
            m_target, m_card_characteristics, getEffectContext());
    }

    ChangeCharacteristicsEffectDefinition::
        ChangeCharacteristicsEffectDefinition(
            core::TargetRequirement target_reqs,
            core::CardCharacteristics characteristics)
        : m_target_requirements(std::move(target_reqs)),
          m_card_characteristics(std::move(characteristics))
    {
        std::cout << "Size of addditional abilities after construction: "
                  << m_card_characteristics.additional_abilities.size() << '\n';
    }

    std::unique_ptr<IOneShotEffect> ChangeCharacteristicsEffectDefinition::bind(
        const core::ExecutionContext exec_ctx, EffectContext context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};
        const auto *card{card_registry.get(context.card_id)};
        auto choices{card->getTargetChoices(*this)};
        auto choice{choices.at(0)};
        context.expires = expires();
        return std::make_unique<ChangeCharacteristicsEffect>(
            choice, m_card_characteristics, context);
    }

    std::unique_ptr<IOneShotEffectDefinition>
    ChangeCharacteristicsEffectDefinition::clone() const
    {
        return std::make_unique<ChangeCharacteristicsEffectDefinition>(
            m_target_requirements, m_card_characteristics);
    }

    const core::TargetRequirement *ChangeCharacteristicsEffectDefinition::
        getTargetRequirement() const
    {
        return &m_target_requirements;
    }

    const core::CardCharacteristics &ChangeCharacteristicsEffectDefinition::
        getCharacteristics() const
    {
        return m_card_characteristics;
    }

    std::unique_ptr<events::IEvent> ChangeCharacteristicsEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        if (!std::holds_alternative<core::Permanent>(m_target))
        {
            throw std::runtime_error(
                "Target for ChangeCharacteristicsEffect was not a Permanent");
        }
        auto permanent_id{std::get<core::Permanent>(m_target)};
        auto *card{card_registry.get(permanent_id)};

        const auto &old_abilities{card->getCurrentAbilities()};
        auto old_characteristics{card->getCharacteristics()};
        for (const auto &ability : old_abilities)
        {
            old_characteristics.additional_abilities.push_back(
                ability.definition().clone());
        }

        card->setCharacteristics(m_card_characteristics, exec_ctx);
        card->setPrevCharacteristics(old_characteristics);

        if (auto expiry = getEffectContext().expires;
            expiry != core::ExpireTime::None)
        {
            if (expiry == core::ExpireTime::EnfOfTurn)
            {
                auto old_characistics{card->getPrevCharacteristics()};
                old_characteristics.loses_all_abilities = true;

                auto context{getEffectContext()};
                context.expires = core::ExpireTime::None;
                auto undo_effect{
                    std::make_unique<ChangeCharacteristicsEffect>(
                        m_target, old_characteristics, context),
                };
                game.addEndOfTurnEffect(std::move(undo_effect));
            }
        }
        return nullptr;
    }
} // namespace dandan::effects
