#ifndef DANDAN_FLYINGABILITY_H
#define DANDAN_FLYINGABILITY_H

#include "dandan/abilities/keywords/IKeyWordAbility.h"
#include "dandan/abilities/keywords/Keyword.h"
#include <memory>
namespace dandan::abilities
{
    class FlyingAbility : public IKeyWordAbility
    {
    public:
        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx,
            AbilityContext context) const override
        {
            return nullptr;
        }

        [[nodiscard]] std::unique_ptr<IAbility> clone() const override
        {
            return std::make_unique<FlyingAbility>();
        }

        [[nodiscard]] Keyword keyword() const override
        {
            return Keyword::Flying;
        }

    private:
    };
} // namespace dandan::abilities

#endif // !DANDAN_FLYINGABILITY_H
