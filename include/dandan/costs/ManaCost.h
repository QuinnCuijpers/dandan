#ifndef DANDAN_MANACOST_H
#define DANDAN_MANACOST_H

#include "ICost.h"
#include "dandan/core/Game.h"
#include "dandan/mana/Mana.h"
#include <memory>

namespace dandan::costs
{
    /** @brief A cost that requires a specific amount of mana to be paid.
     * @class ManaCost
     *
     * @implements ICost
     */
    class ManaCost : public ICost
    {
    public:
        /** Constructs a ManaCost with a specific amount of mana.
         * @param mana The mana requirement for the cost.
         */
        explicit ManaCost(std::unique_ptr<mana::Mana> mana);

        [[nodiscard]] std::string display(
            [[maybe_unused]] bool isFinal = true) const override;

        /** Gets the mana requirement.
         * @return A pointer to the mana requirement.
         */
        [[nodiscard]] mana::Mana *getMana() const;

        [[nodiscard]] bool canPay(const core::Card &source,
                                  const core::Player &player) const override;

        void pay(core::Game &game,
                 abilities::AbilityContext context) const override;

    private:
        std::unique_ptr<mana::Mana> m_mana;
    };
} // namespace dandan::costs

#endif
