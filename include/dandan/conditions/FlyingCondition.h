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
            const core::Game &game,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override
        {
            return std::make_unique<FlyingCondition>();
        }
    };
} // namespace dandan::conditions

#endif