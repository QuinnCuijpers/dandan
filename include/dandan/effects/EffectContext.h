#ifndef DANDAN_EFFECTCONTEXT_H
#define DANDAN_EFFECTCONTEXT_H

#include "dandan/core/CardID.h"
#include "dandan/core/PlayerID.h"
#include <optional>

namespace dandan::effects
{
    class EffectContext
    {
    public:
        EffectContext() = default;
        EffectContext(core::CardID card_id)
            : EffectContext(card_id, std::nullopt)
        {
        }

        EffectContext(core::PlayerID player_id)
            : EffectContext(std::nullopt, player_id)
        {
        }

        [[nodiscard]] std::optional<core::PlayerID> player() const
        {
            return m_player_id;
        }

        [[nodiscard]] std::optional<core::CardID> card() const
        {
            return m_card_id;
        }

    private:
        std::optional<core::CardID> m_card_id;
        std::optional<core::PlayerID> m_player_id;

        EffectContext(std::optional<core::CardID> card_id = std::nullopt,
                      std::optional<core::PlayerID> player = std::nullopt)
            : m_card_id(card_id), m_player_id(player)
        {
        }
    };
} // namespace dandan::effects

#endif