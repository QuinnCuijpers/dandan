#include "dandan/costs/ManaCost.h"
#include "dandan/mana/Manapool.h"

namespace dandan::costs
{

    ManaCost::ManaCost(std::unique_ptr<mana::Manapool> mana)
        : m_mana{std::move(mana)} {};

    std::string ManaCost::display([[maybe_unused]] bool isFinal) const
    {
        std::string res{};
        res += mana::ManaToSymbols(m_mana->getMana());
        return res;
    }

    [[nodiscard]] mana::Manapool *ManaCost::getMana() const
    {
        return m_mana.get();
    }

    [[nodiscard]] bool ManaCost::canPay(
        [[maybe_unused]] const core::Card &source,
        const core::Player &player) const
    {
        return player.manaPool().canPay(*m_mana);
    }

    void ManaCost::pay([[maybe_unused]] core::Game &game,
                       [[maybe_unused]] abilities::AbilityContext context) const
    {
        auto &player = game.getPlayer(context.controller_id);
        player.manaPool().pay(*m_mana);
    }

} // namespace dandan::costs
