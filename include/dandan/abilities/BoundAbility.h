#ifndef DANDAN_BOUND_ABILITY_H
#define DANDAN_BOUND_ABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include <optional>

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
        BoundAbility(const IAbility &definition, core::CardID source_card,
                     core::PlayerID source_player,
                     std::optional<size_t> chosen_mode_index = std::nullopt)
            : BoundAbility(
                  definition,
                  AbilityContext{source_card, source_player, chosen_mode_index})
        {
        }

        /** Create a bound ability from a definition and context.
         * @param definition The ability definition.
         * @param context The ability context.
         */
        BoundAbility(const IAbility &definition, AbilityContext context)
            : m_definition(&definition), m_source_card(context.source_card_id),
              m_source_player(context.controller_id),
              m_chosen_mode_index(context.chosen_mode_index)
        {
        }

        /** Get the underlying ability definition.
         * @return The ability definition.
         */
        [[nodiscard]] const IAbility &definition() const
        {
            return *m_definition;
        }

        /** Get the source card ID.
         * @return The source card ID.
         */
        [[nodiscard]] core::CardID sourceCard() const
        {
            return m_source_card;
        }

        /** Get the source player ID.
         * @return The source player ID.
         */
        [[nodiscard]] core::PlayerID sourcePlayer() const
        {
            return m_source_player;
        }

        /** Create an effect instance for this ability.
         * @param game The game instance.
         * @return The created effect instance.
         */
        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) const
        {
            AbilityContext context{m_source_card, m_source_player,
                                   m_chosen_mode_index};
            return m_definition->createEffect(game, context);
        }

    private:
        const IAbility *m_definition;
        core::CardID m_source_card;
        core::PlayerID m_source_player;
        std::optional<size_t> m_chosen_mode_index;
    };
} // namespace dandan::abilities

#endif