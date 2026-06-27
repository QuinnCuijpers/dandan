#ifndef DANDAN_BLOCKACTION_H
#define DANDAN_BLOCKACTION_H

#include "dandan/core/CardID.h"
#include "dandan/core/actions/IAction.h"
#include <stdexcept>
namespace dandan::core
{
    class BlockAction : public IAction
    {

    public:
        BlockAction(CardID blocker, CardID attacker)
            : m_blocker(blocker), m_attacker(attacker)
        {
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            [[maybe_unused]] core::Game &game) override
        {
            throw std::runtime_error(
                "Creating block effect not yet implemented");
        }

        [[nodiscard]] CardID getAttacker() const
        {
            return m_attacker;
        }

        [[nodiscard]] CardID getBlocker() const
        {
            return m_blocker;
        }

    private:
        CardID m_blocker;
        CardID m_attacker;
    };
} // namespace dandan::core

#endif