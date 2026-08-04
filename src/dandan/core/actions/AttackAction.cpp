#include "dandan/core/actions/AttackAction.h"

namespace dandan::core
{
    AttackAction::AttackAction(core::Card &creature) : m_creature{creature}
    {
    }

    [[nodiscard]] ActionActor AttackAction::getActor() const
    {
        return m_creature.getID();
    }

    std::unique_ptr<effects::IOneShotEffect> AttackAction::createEffect(
        [[maybe_unused]] core::Game &game)
    {
        std::cout << "Executing attack action\n";
        effects::EffectContext context{m_creature.getID()};
        return std::make_unique<effects::AttackEffect>(m_creature, context);
    }
} // namespace dandan::core
