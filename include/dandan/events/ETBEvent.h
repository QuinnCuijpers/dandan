#ifndef ENTERS_BATTLE_FIELD_EVENT_H
#define ENTERS_BATTLE_FIELD_EVENT_H

#include "IEvent.h"
#include <optional>

namespace dandan::events
{

    struct ETBEvent final : public IEvent
    {
        std::optional<bool> m_tapped{};

        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }
        bool isTapped() const
        {
            return m_tapped.value_or(false);
        }

        void to_json(nlohmann::json &j, const IEvent &event) const override;
    };
} // namespace dandan::events

#endif