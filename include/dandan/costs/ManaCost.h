#ifndef DANDAN_MANACOST_H
#define DANDAN_MANACOST_H

#include "ICost.h"
#include "dandan/mana/Mana.h"
#include <memory>

namespace dandan::costs
{
    class ManaCost : public ICost
    {
    public:
        explicit ManaCost(std::unique_ptr<mana::Mana> mana)
            : m_mana{std::move(mana)} {};

        [[nodiscard]] mana::Mana *getMana() const
        {
            return m_mana.get();
        }

        void evaluate() override;

    private:
        std::unique_ptr<mana::Mana> m_mana;
    };
} // namespace dandan::costs

#endif