#ifndef DANDAN_BASICLANDABILITY_H
#define DANDAN_BASICLANDABILITY_H

#include "dandan/abilities/AbilityContext.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/core/ExecutionContext.h"
#include <memory>
#include <unordered_map>

namespace dandan::abilities
{

    /** @brief An ability that represents a basic land's ability to produce
     * mana.
     * @class BasicLandAbility
     *
     * @implements IAbility
     */
    class BasicLandAbility final : public IAbility
    {
    public:
        BasicLandAbility();

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::string displayOption(
            [[maybe_unused]] size_t index) const override;

        [[nodiscard]] bool canActivate(
            [[maybe_unused]] core::ExecutionContext exec_ctx,
            [[maybe_unused]] const AbilityContext &context) const override;

        /** @brief Get the number of options for the ability
         * @return The number of options
         */
        [[nodiscard]] size_t optionsAmount() const override;

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx,
            AbilityContext context) const override;

        const ManaAbility *getManaAbility(core::ExecutionContext exec_ctx,
                                          const AbilityContext &context) const;

    private:
        const std::unordered_map<core::SubType, std::unique_ptr<ManaAbility>>
            m_basic_land_ability_map;
    };
} // namespace dandan::abilities

#endif
