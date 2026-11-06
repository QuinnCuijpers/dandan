#ifndef DANDAN_BOUND_ABILITY_H
#define DANDAN_BOUND_ABILITY_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/AbilityType.h"
#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/TextReplacement.h"
#include <optional>
#include <vector>

namespace dandan::core
{
    class Card;
    struct ExecutionContext;
} // namespace dandan::core

namespace dandan::effects
{
    class IOneShotEffect;
}
namespace dandan::abilities
{
    class IAbility;

    /** @brief An ability that is bound to a specific source card and player.
     * @class BoundAbility
     */
    class BoundAbility
    {
    public:
        /** Create a bound ability from a definition and context.
         * @param definition The ability definition.
         * @param source_card The source card ID.
         * @param chosen_mode_index The index of the chosen mode.
         * @param text_replacements The text replacements to apply to the
         * ability
         */
        BoundAbility(const IAbility &definition, core::Card *source_card,
                     std::optional<size_t> chosen_mode_index = std::nullopt,
                     std::optional<std::vector<core::TextReplacement>>
                         text_replacements = std::nullopt);

        /** Get the underlying ability definition.
         * @return The ability definition.
         */
        [[nodiscard]] const IAbility &definition() const;

        /**
         * @brief Get the accosiated ability type
         * @return The accosiated type
         */
        [[nodiscard]] AbilityType::Type type() const;

        /** Get the source card ID.
         * @return The source card ID.
         */
        [[nodiscard]] core::CardID sourceCard() const;

        /** Get the source player ID.
         * @return The source player ID.
         */
        [[nodiscard]] core::PlayerID sourcePlayer() const;

        /** Create an effect instance for this ability.
         * @param exec_ctx The game execution context.
         * @return The created effect instance.
         */
        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx) const;

        /**
         * @brief Add a text replacement to the ability
         * @param text_replacement The text replacement to add
         */
        void addTextReplacement(core::TextReplacement text_replacement);

        /**
         * @brief Generate an ability context for the ability
         * @return The ability context for this ability
         */
        [[nodiscard]] AbilityContext getContext() const;

        /**
         * @brief Equality operator for bound abilities
         * @param ability The ability to compare to
         * @return Whether the bound abilities are equal
         */
        bool operator==(const BoundAbility &ability) const;

    private:
        const IAbility *m_definition{};
        const core::Card *m_source_card{};
        AbilityType m_ability_type;
        std::optional<size_t> m_chosen_mode_index;
        std::optional<std::vector<core::TextReplacement>> m_text_replacement;
    };
} // namespace dandan::abilities

#endif
