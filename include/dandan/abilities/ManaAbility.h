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
    /** An ability that produces mana
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
        explicit ManaAbility(mana::ManaList manaList)
            : m_mana_list(std::move(manaList))
        {
        }

        /** Constructor
         * @param cost The cost to activate the ability
         * @param manaList The list of mana to produce
         */
        ManaAbility(std::unique_ptr<costs::ICost> cost, mana::ManaList manaList)
            : m_cost(std::move(cost)), m_mana_list(std::move(manaList))
        {
        }

        /** Get the mana produced by the ability
         * @return The mana produced by the ability
         */
        [[nodiscard]] const mana::ManaList *getManaList() const
        {
            return &m_mana_list;
        }

        /** Get the cost of the ability
         * @return The cost of the ability
         */
        [[nodiscard]] const costs::ICost *getCost() const
        {
            return m_cost.get();
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override;

        [[nodiscard]] bool canActivate(core::Game &game,
                                       AbilityContext context) const override;

    private:
        std::unique_ptr<costs::ICost> m_cost{
            std::make_unique<costs::TapCost>()};
        mana::ManaList m_mana_list;
    };
} // namespace dandan::abilities

#endif // DANDAN_MANAABILITY_H