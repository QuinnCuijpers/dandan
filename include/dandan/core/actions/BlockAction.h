#ifndef DANDAN_BLOCKACTION_H
#define DANDAN_BLOCKACTION_H

#include "dandan/core/CardID.h"
#include "dandan/core/actions/IAction.h"
namespace dandan::core
{
    /** @brief An action that makes one creature block another.
     * @class BlockAction
     */
    class BlockAction : public IAction
    {

    public:
        /** Constructs a block action.
         * @param blocker The card ID of the blocking creature.
         * @param attacker The card ID of the attacking creature.
         */
        BlockAction(CardID blocker, CardID attacker);

        /** Creates the effect that performs the block.
         * @param exec_ctx The execution context.
         * @return The effect that performs the block.
         */
        std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::ExecutionContext exec_ctx) override;

        /** Gets the attacking creature.
         * @return The card ID of the attacking creature.
         */
        [[nodiscard]] CardID getAttacker() const;

        /** Gets the blocking creature.
         * @return The card ID of the blocking creature.
         */
        [[nodiscard]] CardID getBlocker() const;

    private:
        CardID m_blocker;
        CardID m_attacker;
    };
} // namespace dandan::core

#endif
