#ifndef DANDAN_BLOCKACTION_H
#define DANDAN_BLOCKACTION_H

#include "dandan/core/CardID.h"
#include "dandan/core/actions/IAction.h"
namespace dandan::core
{
    class BlockAction : public IAction
    {

    public:
        BlockAction(CardID blocker, CardID attacker);

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::Game &game) override;

        [[nodiscard]] CardID getAttacker() const;

        [[nodiscard]] CardID getBlocker() const;

    private:
        CardID m_blocker;
        CardID m_attacker;
    };
} // namespace dandan::core

#endif
