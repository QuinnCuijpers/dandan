#ifndef DANDAN_IONESHOTEFFECTDEFINITION_H
#define DANDAN_IONESHOTEFFECTDEFINITION_H

#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <string>
namespace dandan::effects
{

    class IOneShotEffectDefinition
    {
    public:
        IOneShotEffectDefinition() = default;
        IOneShotEffectDefinition(const IOneShotEffectDefinition &) = delete;
        IOneShotEffectDefinition(IOneShotEffectDefinition &&) = delete;
        IOneShotEffectDefinition &operator=(const IOneShotEffectDefinition &) =
            delete;
        IOneShotEffectDefinition &operator=(IOneShotEffectDefinition &&) =
            delete;
        virtual ~IOneShotEffectDefinition() = default;

        [[nodiscard]] virtual std::unique_ptr<IOneShotEffect> bind(
            core::Game &game, EffectContext context) const = 0;

        [[nodiscard]] virtual std::string display() const
        {
            throw std::runtime_error("Unimplemented display for definition");
        }

        [[nodiscard]] virtual std::unique_ptr<IOneShotEffectDefinition> clone()
            const = 0;

        [[nodiscard]] virtual const core::TargetRequirement *
        getTargetRequirement() const
        {
            return nullptr;
        }
    };
} // namespace dandan::effects

#endif