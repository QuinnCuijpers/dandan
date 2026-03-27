#ifndef TRIGGEREDABILITY_H
#define TRIGGEREDABILITY_H

#include "IAbility.h"
#include "Events.h"

namespace dandan::abilities
{

    class ITriggeredEffect
    {
    public:
        virtual void apply() = 0;
        virtual ~ITriggeredEffect() = default;
        virtual void from_json(const nlohmann::json &j, ITriggeredEffect &effect) = 0;
        virtual void to_json(nlohmann::json &j, const ITriggeredEffect &effect) = 0;
    };

    class ScryEffect : public ITriggeredEffect
    {
    public:
        void apply() override;
        void from_json(const nlohmann::json &j, ITriggeredEffect &effect) override;
        void to_json(nlohmann::json &j, const ITriggeredEffect &effect) override;

    private:
        int m_scry_amount{1};
    };

    class PeekEffect : public ITriggeredEffect
    {
    public:
        PeekEffect(int peek_amount) : m_peek_amount(peek_amount) {}
        void apply() override;
        void from_json(const nlohmann::json &j, ITriggeredEffect &effect) override;
        void to_json(nlohmann::json &j, const ITriggeredEffect &effect) override;

    private:
        int m_peek_amount{3};
    };

    class TriggeredAbility : public IAbility
    {
    public:
        TriggeredAbility(std::unique_ptr<IEvent> on, std::unique_ptr<ITriggeredEffect> effect)
            : m_on(std::move(on)), m_effect(std::move(effect)) {}

        void resolve() override;

        void from_json(const nlohmann::json &j, IAbility &ability) override;

        void to_json(nlohmann::json &j, const IAbility &ability) override;

    private:
        std::unique_ptr<IEvent> m_on;
        std::unique_ptr<ITriggeredEffect> m_effect;
    };
}

#endif