#include "dandan/abilities/keywords/FlashbackAbility.h"

namespace dandan::abilities
{
    Keyword FlashbackAbility::keyword() const
    {
        return Keyword::Flashback;
    }

    std::unique_ptr<effects::IOneShotEffect> FlashbackAbility::createEffect(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] AbilityContext context) const
    {
        return nullptr;
    }

    FlashbackAbility::FlashbackAbility(mana::ManaPrice cost)
        : m_cost(std::move(cost))
    {
    }

    const mana::ManaPrice &FlashbackAbility::getCost() const
    {
        return m_cost;
    }

    std::unique_ptr<IAbility> FlashbackAbility::clone() const
    {
        return std::make_unique<FlashbackAbility>(m_cost);
    }
} // namespace dandan::abilities
