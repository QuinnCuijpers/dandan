#ifndef EVENTS_H
#define EVENTS_H

#include <optional>
#include <nlohmann/json_fwd.hpp>

namespace dandan::abilities
{

    class IEvent
    {
    public:
        virtual ~IEvent() = default;
        virtual void to_json(nlohmann::json &j, const IEvent &event) const = 0;
    };

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