#ifndef DANDAN_ATTACKPREVENTIONEFFECT_H
#define DANDAN_ATTACKPREVENTIONEFFECT_H

#include "IPreventionEffect.h"
#include "dandan/conditions/ICondition.h"
#include <memory>

namespace dandan::effects
{
    class AttackPreventionEffect : public IPreventionEffect
    {
    public:
        explicit AttackPreventionEffect(
            std::unique_ptr<conditions::ICondition> condition)
            : m_condition(std::move(condition))
        {
        }

        [[nodiscard]] const conditions::ICondition *getCondition() const
        {
            return m_condition.get();
        }

        bool prevents(const core::IAction &action,
                      const core::Game &game) override;

    private:
        std::unique_ptr<conditions::ICondition> m_condition;
    };

} // namespace dandan::effects

#endif // DANDAN_ATTACKPREVENTIONEFFECT_H