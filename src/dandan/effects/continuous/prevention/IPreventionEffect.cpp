#include "dandan/effects/continuous/prevention/IPreventionEffect.h"

namespace dandan::effects
{
    IPreventionEffect::IPreventionEffect(
        std::unique_ptr<conditions::ICondition> condition)
        : m_condition(std::move(condition))
    {
    }

    std::unique_ptr<IContinuousEffect> IPreventionEffect::cloneContinuous()
        const
    {
        return clone();
    }

    const conditions::ICondition *IPreventionEffect::getCondition() const
    {
        return m_condition.get();
    }

    std::unique_ptr<conditions::ICondition> IPreventionEffect::cloneCondition()
        const
    {
        return m_condition->clone();
    }
} // namespace dandan::effects
