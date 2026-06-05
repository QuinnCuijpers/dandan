#ifndef DANDAN_BOUND_ABILITY_H
#define DANDAN_BOUND_ABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include <optional>

namespace dandan::abilities
{
    class BoundAbility
    {
    public:
        BoundAbility(const IAbility &definition, core::CardID source_card,
                     core::PlayerID source_player,
                     std::optional<size_t> chosen_mode_index = std::nullopt)
            : m_definition(&definition), m_source_card(source_card),
              m_source_player(source_player),
              m_chosen_mode_index(chosen_mode_index)
        {
        }

        BoundAbility(const IAbility &definition, AbilityContext context)
            : m_definition(&definition), m_source_card(context.source_card_id),
              m_source_player(context.controller_id),
              m_chosen_mode_index(context.chosen_mode_index)
        {
        }

        [[nodiscard]] const IAbility &definition() const
        {
            return *m_definition;
        }

        [[nodiscard]] core::CardID sourceCard() const
        {
            return m_source_card;
        }

        [[nodiscard]] core::PlayerID sourcePlayer() const
        {
            return m_source_player;
        }

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