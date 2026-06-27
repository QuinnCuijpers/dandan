#ifndef DANDAN_BLOCKPREVENTIONEFFECT_H
#define DANDAN_BLOCKPREVENTIONEFFECT_H

#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>
namespace dandan::effects
{
    class BlockPreventionEffect : public IPreventionEffect
    {

    public:
        explicit BlockPreventionEffect(
            std::unique_ptr<conditions::ICondition> condition)
            : IPreventionEffect(std::move(condition))
        {
        }

        [[nodiscard]] bool prevents(const core::IAction &action,
                                    const core::Game &game,
                                    std::optional<effects::EffectContext>
                                        context = std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<IPreventionEffect> clone() const override
        {
            return std::make_unique<BlockPreventionEffect>(cloneCondition());
        }
    };
} // namespace dandan::effects

#endif