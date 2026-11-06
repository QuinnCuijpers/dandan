#ifndef IABILITYDECORATOR_H
#define IABILITYDECORATOR_H

#include "IAbility.h"
#include "dandan/core/ExecutionContext.h"
#include <memory>

namespace dandan::abilities
{
    /** @brief An interface for ability decorators to use the decorator pattern
     * with abilities
     * @class IAbilityDecorator
     *
     * @implements IAbility
     */
    struct IAbilityDecorator : public IAbility
    {
    public:
        /// The ability being decorated
        std::unique_ptr<IAbility> m_ability;

        /** Constructor
         * @param ability The ability to decorate
         */
        explicit IAbilityDecorator(std::unique_ptr<IAbility> ability);

        /**
         * Get the inner ability being decorated
         * @return The inner ability being decorated
         */
        [[nodiscard]] const IAbility *getInnerAbility() const;

        [[nodiscard]] bool canActivate(
            core::ExecutionContext exec_ctx,
            const AbilityContext &context) const override;

        [[nodiscard]] size_t optionsAmount() const override;
    };
} // namespace dandan::abilities

#endif
