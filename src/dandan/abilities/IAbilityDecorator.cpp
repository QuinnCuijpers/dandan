#include "dandan/abilities/IAbilityDecorator.h"

namespace dandan::abilities
{
    IAbilityDecorator::IAbilityDecorator(std::unique_ptr<IAbility> ability)
        : m_ability{std::move(ability)} {};

    const IAbility *IAbilityDecorator::getInnerAbility() const
    {
        return m_ability.get();
    }

    bool IAbilityDecorator::canActivate(core::ExecutionContext exec_ctx,
                                        const AbilityContext &context) const
    {
        return m_ability->canActivate(exec_ctx, context);
    }

    size_t IAbilityDecorator::optionsAmount() const
    {
        return m_ability->optionsAmount();
    }
} // namespace dandan::abilities
