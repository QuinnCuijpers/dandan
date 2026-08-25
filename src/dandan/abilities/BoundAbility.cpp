#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/Card.h"
#include "dandan/core/CardID.h"

namespace dandan::abilities
{

    BoundAbility::BoundAbility(
        const IAbility &definition, core::Card *source_card,
        std::optional<size_t> chosen_mode_index,
        std::optional<std::vector<core::TextReplacement>> text_replacements)
        : m_definition(&definition), m_source_card(source_card),
          m_ability_type(AbilityType::from(&definition)),
          m_chosen_mode_index(chosen_mode_index),
          m_text_replacement(std::move(text_replacements))
    {
    }
    core::CardID BoundAbility::sourceCard() const
    {
        return m_source_card->getID();
    }

    [[nodiscard]] core::PlayerID BoundAbility::sourcePlayer() const
    {
        return m_source_card->getControllerID();
    }

    [[nodiscard]] const IAbility &BoundAbility::definition() const
    {
        return *m_definition;
    }

    [[nodiscard]] AbilityType::Type BoundAbility::type() const
    {
        return m_ability_type.getType();
    }

    [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> BoundAbility::
        createEffect(core::ExecutionContext exec_ctx) const
    {
        AbilityContext context{m_source_card->getID(),
                               m_source_card->getControllerID(),
                               m_chosen_mode_index, m_text_replacement};
        auto effect{m_definition->createEffect(exec_ctx, context)};
        return effect;
    }

    void BoundAbility::addTextReplacement(
        core::TextReplacement text_replacement)
    {
        if (m_text_replacement.has_value())
        {
            m_text_replacement->push_back(text_replacement);
        }
        else
        {
            m_text_replacement =
                std::vector<core::TextReplacement>{text_replacement};
        }
    }

    AbilityContext BoundAbility::getContext() const
    {
        return {sourceCard(), sourcePlayer(), m_chosen_mode_index,
                m_text_replacement};
    }

    bool BoundAbility::operator==(const BoundAbility &ability) const
    {
        return ability.m_ability_type.getType() == m_ability_type.getType() &&
               m_definition == ability.m_definition &&
               m_source_card == ability.m_source_card;
    }

} // namespace dandan::abilities
