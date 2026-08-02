#ifndef DANDAN_MANAABILITY_H
#define DANDAN_MANAABILITY_H

#include "IAbility.h"
#include "dandan/core/Game.h"
#include "dandan/costs/ICost.h"
#include "dandan/costs/TapCost.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/mana/ManaList.h"
#include <memory>

namespace dandan::abilities
{
    /** @brief An ability that produces mana
     * @class ManaAbility
     *
     * @implements IAbility
     */
    class ManaAbility final : public IAbility
    {
    public:
        /** Constructor
         * @param manaList The list of mana to produce
         */
        explicit ManaAbility(mana::ManaList manaList);

        /** Constructor
         * @param cost The cost to activate the ability
         * @param manaList The list of mana to produce
         */
        ManaAbility(std::unique_ptr<costs::ICost> cost,
                    mana::ManaList manaList);

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::string displayOption(size_t index) const override;

        /** Get the mana produced by the ability
         * @return The mana produced by the ability
         */
        [[nodiscard]] const mana::ManaList *getManaList() const;

        /** Get the cost of the ability
         * @return The cost of the ability
         */
        [[nodiscard]] const costs::ICost *getCost() const;

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

        [[nodiscard]] bool canActivate(
            core::Game &game, const AbilityContext &context) const override;

        [[nodiscard]] size_t optionsAmount() const override;

    private:
        std::unique_ptr<costs::ICost> m_cost{
            std::make_unique<costs::TapCost>()};
        mana::ManaList m_mana_list;
    };
} // namespace dandan::abilities

#endif // DANDAN_MANAABILITY_H
