#ifndef REPLACEMENTABILITY_H
#define REPLACEMENTABILITY_H

#include "IAbility.h"
#include "Events.h"
#include <functional>
#include <memory>

namespace dandan::abilities
{

    class IReplacementEffect
    {
    public:
        virtual std::unique_ptr<IEvent> replace(IEvent &event) = 0;
        virtual ~IReplacementEffect() = default;

        virtual void from_json(const nlohmann::json &j, IReplacementEffect &effect) = 0;
        virtual void to_json(nlohmann::json &j, const IReplacementEffect &effect) = 0;
    };

    class EntersTappedEffect : public IReplacementEffect
    {
    public:
        std::unique_ptr<IEvent> replace(IEvent &event) override;

        void from_json(const nlohmann::json &j, IReplacementEffect &effect) override;

        void to_json(nlohmann::json &j, const IReplacementEffect &effect) override;
    };

    class ReplacementAbility : public IAbility
    {
    public:
        ReplacementAbility() = default;
        ReplacementAbility(std::unique_ptr<IEvent> event, std::unique_ptr<IReplacementEffect> replace_effect)
            : m_event(std::move(event)), m_replace_effect(std::move(replace_effect)) {}

        void resolve() override;

        void from_json(const nlohmann::json &j, IAbility &ability) override;

        void to_json(nlohmann::json &j, const IAbility &ability) override;

    private:
        std::unique_ptr<IEvent> m_event;
        std::unique_ptr<IReplacementEffect> m_replace_effect;
    };
}

#endif