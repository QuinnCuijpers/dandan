#ifndef DANDAN_MANAABILITY_H
#define DANDAN_MANAABILITY_H

#include "IAbility.h"
#include "dandan/costs/ICost.h"
#include "dandan/costs/TapCost.h"
#include "dandan/mana/ManaList.h"
#include <memory>

namespace dandan::abilities
{

    class ManaAbility final : public IAbility
    {
    public:
        explicit ManaAbility(mana::ManaList manaList)
            : m_mana_list(std::move(manaList))
        {
        }

        ManaAbility(std::unique_ptr<costs::ICost> cost, mana::ManaList manaList)
            : m_cost(std::move(cost)), m_mana_list(std::move(manaList))
        {
        }

        [[nodiscard]] const mana::ManaList *getMana() const
        {
            return &m_mana_list;
        }

        [[nodiscard]] const costs::ICost *getCost() const
        {
            return m_cost.get();
        }

        void resolve() const override;

    private:
        std::unique_ptr<costs::ICost> m_cost{
            std::make_unique<costs::TapCost>()};
        mana::ManaList m_mana_list;
    };
} // namespace dandan::abilities

#endif // DANDAN_MANAABILITY_H