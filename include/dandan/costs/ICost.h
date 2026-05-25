#ifndef DANDAN_I_COST
#define DANDAN_I_COST

#include "dandan/core/Player.h"
namespace dandan::costs
{
    /** Base class for all cost types.
     * @class ICost
     */
    class ICost
    {
    public:
        ICost() = default;
        ICost(const ICost &) = delete;
        ICost(ICost &&) = delete;
        ICost &operator=(const ICost &) = delete;
        ICost &operator=(ICost &&) = delete;
        virtual ~ICost() = default;

        /** Checks if the cost can be paid.
         * @param source The card generating the cost.
         * @param player The player paying the cost.
         * @return True if the cost can be paid, false otherwise.
         */
        [[nodiscard]] virtual bool canPay(const core::Card &source,
                                          const core::Player &player) const = 0;

        /** Pays the cost by mutating the game state.
         * @param game The game instance to mutate when paying the cost.
         * @param context The ability context.
         */
        virtual void pay(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] abilities::AbilityContext context) const = 0;
    };
} // namespace dandan::costs

#endif