#ifndef ENTERS_BATTLE_FIELD_EVENT_H
#define ENTERS_BATTLE_FIELD_EVENT_H

#include "IEvent.h"

namespace dandan::events
{

    class EntersBattlefieldEvent : public IEvent
    {
    public:
        void setTapped(bool tapped) { m_tapped = tapped; }
        bool isTapped() const { return m_tapped.value_or(false); }

        void to_json(nlohmann::json &j, const IEvent &event) const override;

    private:
        std::optional<bool> m_tapped{};
    };
}

#endif