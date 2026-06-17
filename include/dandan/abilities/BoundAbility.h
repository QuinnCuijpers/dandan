#ifndef DANDAN_BOUND_ABILITY_H
#define DANDAN_BOUND_ABILITY_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/TextReplacement.h"
#include <optional>
#include <utility>
#include <vector>

namespace dandan::core
{
    class Card;
}

namespace dandan::abilities
{
    /** @brief An ability that is bound to a specific source card and player.
     * @class BoundAbility
     */
    class BoundAbility
    {
    public:
        /** Create a bound ability from a definition and context.
         * @param definition The ability definition.
         * @param source_card The source card ID.
         * @param source_player The source player ID.
         * @param chosen_mode_index The index of the chosen mode.
         */
        BoundAbility(const IAbility &definition, core::Card *source_card,
                     std::optional<size_t> chosen_mode_index = std::nullopt,
                     std::optional<std::vector<core::TextReplacement>>
                         text_replacements = std::nullopt)
            : m_definition(&definition), m_source_card(source_card),
              m_ability_type(AbilityType::from(&definition)),
              m_chosen_mode_index(chosen_mode_index),
              m_text_replacement(std::move(text_replacements))
        {
        }

        /** Get the underlying ability definition.
         * @return The ability definition.
         */
        [[nodiscard]] const IAbility &definition() const
        {
            return *m_definition;
        }

        [[nodiscard]] AbilityType::Type type() const
        {
            return m_ability_type.getType();
        }

        /** Get the source card ID.
         * @return The source card ID.
         */
        [[nodiscard]] core::CardID sourceCard() const;

        /** Get the source player ID.
         * @return The source player ID.
         */
        [[nodiscard]] core::PlayerID sourcePlayer() const;

        /** Create an effect instance for this ability.
         * @param game The game instance.
         * @return The created effect instance.
         */
        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) const;

        void addTextReplacement(core::TextReplacement text_replacement)
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

        [[nodiscard]] AbilityContext getContext() const;

        bool operator==(const BoundAbility &ability) const
        {
            return ability.m_ability_type.getType() ==
                       m_ability_type.getType() &&
                   m_definition == ability.m_definition &&
                   m_source_card == ability.m_source_card;
        }

    private:
        const IAbility *m_definition{};
        const core::Card *m_source_card{};
        AbilityType m_ability_type;
        std::optional<size_t> m_chosen_mode_index;
        std::optional<std::vector<core::TextReplacement>> m_text_replacement;
    };
} // namespace dandan::abilities

#endif