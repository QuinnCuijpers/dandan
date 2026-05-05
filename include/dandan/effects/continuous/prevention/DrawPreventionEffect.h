#ifndef DANDAN_DRAW_PREVENTION_EFFECT_H
#define DANDAN_DRAW_PREVENTION_EFFECT_H

#include "dandan/conditions/ICondition.h"
#include "dandan/effects/continuous/prevention/IPreventionEffect.h"
#include <memory>

namespace dandan::effects
{
    class DrawPreventionEffect : public IPreventionEffect
    {
    public:
        explicit DrawPreventionEffect(
            std::unique_ptr<conditions::ICondition> condition)
            : m_condition(std::move(condition))
        {
        }

        [[nodiscard]] bool prevents(const core::IAction &action,
                                    const core::Game &game) override;

    private:
        std::unique_ptr<conditions::ICondition> m_condition;
    };
} // namespace dandan::effects

#endif