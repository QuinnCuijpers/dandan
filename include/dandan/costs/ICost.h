#ifndef DANDAN_I_COST
#define DANDAN_I_COST

#include "dandan/core/Player.h"
namespace dandan::costs
{
    class ICost
    {
    public:
        ICost() = default;
        ICost(const ICost &) = delete;
        ICost(ICost &&) = delete;
        ICost &operator=(const ICost &) = delete;
        ICost &operator=(ICost &&) = delete;
        virtual ~ICost() = default;

        [[nodiscard]] virtual bool canPay(const core::Card &source,
                                          const core::Player &player) const = 0;
        virtual void pay(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] abilities::AbilityContext context) const = 0;
    };
} // namespace dandan::costs

#endif