#include "dandan/core/actions/BlockAction.h"
namespace dandan::core
{
    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    BlockAction::BlockAction(CardID blocker, CardID attacker)
        : m_blocker(blocker), m_attacker(attacker)
    {
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)

    std::unique_ptr<effects::IOneShotEffect> BlockAction::createEffect(
        [[maybe_unused]] core::Game &game)
    {
        throw std::runtime_error("Creating block effect not yet implemented");
    }

    [[nodiscard]] CardID BlockAction::getAttacker() const
    {
        return m_attacker;
    }

    [[nodiscard]] CardID BlockAction::getBlocker() const
    {
        return m_blocker;
    }
} // namespace dandan::core
