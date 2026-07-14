#include "dandan/core/Battlefield.h"
#include "dandan/core/Expire.h"
#include "dandan/effects/one_shot/ChangeCharasticsEffect.h"
#include "dandan/events/IEvent.h"
#include <memory>
#include <stdexcept>
#include <variant>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ChangeCharacteristicsEffect::apply_impl(
        core::Game &game) const
    {
        if (!std::holds_alternative<core::Permanent>(m_target))
        {
            throw std::runtime_error(
                "Target for ChangeCharacteristicsEffect was not a Permanent");
        }
        auto permanent_id{std::get<core::Permanent>(m_target)};
        auto *card{game.getCardByID(permanent_id)};
        auto old_characteristics{card->getCharacteristics()};
        card->setCharacteristics(m_card_characteristics, game);
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
                auto undo_effect{std::make_unique<ChangeCharacteristicsEffect>(
                    m_target, old_characteristics, context)};
                game.addEndOfTurnEffect(std::move(undo_effect));
            }
        }
        return nullptr;
    }
} // namespace dandan::effects