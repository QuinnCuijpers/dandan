#ifndef REPLACEMENTABILITY_H
#define REPLACEMENTABILITY_H

#include "IAbility.h"
#include "dandan/effects/IEffect.h"
#include "dandan/replacement_effects/IReplacementEffect.h"
#include <memory>

namespace dandan::abilities
{

    // TODO: extend this class to support more static abilities.
    class StaticAbility final : public IAbility
    {
    public:
        StaticAbility() = default;
        StaticAbility(
            std::unique_ptr<dandan::effects::IEffect> on_effect,
            std::unique_ptr<dandan::replacement_effects::IReplacementEffect>
                replacement_effect)
            : m_on_effect(std::move(on_effect)),
              m_replacement_effect(std::move(replacement_effect))
        {
        }

        void resolve() const override;

        const dandan::effects::IEffect *getOnEffect() const
        {
            return m_on_effect.get();
        }
        const dandan::replacement_effects::IReplacementEffect *
        getReplacementEffect() const
        {
            return m_replacement_effect.get();
        }

    private:
        std::unique_ptr<dandan::effects::IEffect> m_on_effect;
        std::unique_ptr<dandan::replacement_effects::IReplacementEffect>
            m_replacement_effect;
    };
} // namespace dandan::abilities

#endif