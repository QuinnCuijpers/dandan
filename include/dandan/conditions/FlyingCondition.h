#ifndef DANDAN_FLYINGCONDITION_H
#define DANDAN_FLYINGCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <memory>
namespace dandan::conditions
{
    class FlyingCondition : public ICondition
    {

    public:
        [[nodiscard]] bool isSatisfied(
            core::ExecutionContext exec_ctx,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;
    };
} // namespace dandan::conditions

#endif
