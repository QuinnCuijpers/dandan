#ifndef DANDAN_MANAABILITY_H
#define DANDAN_MANAABILITY_H

#include "IAbility.h"
#include "dandan/mana/ManaList.h"

namespace dandan::abilities
{

    class ManaAbility final : public IAbility
    {
    public:
        explicit ManaAbility(mana::ManaList manaList)
            : m_mana_list(std::move(manaList))
        {
        }

        [[nodiscard]] const mana::ManaList *getMana() const
        {
            return &m_mana_list;
        }

        void resolve() const override;

    private:
        mana::ManaList m_mana_list;
    };
} // namespace dandan::abilities

#endif // DANDAN_MANAABILITY_H