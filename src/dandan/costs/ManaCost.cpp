#include "dandan/costs/ManaCost.h"
#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaPrice.h"
#include <string>

namespace dandan::costs
{

    ManaCost::ManaCost(mana::ManaPrice price) : m_mana{std::move(price)} {};

    std::string ManaCost::display([[maybe_unused]] bool isFinal) const
    {
        std::string res{};
        auto generic_str = m_mana.generic() != 0
                               ? "(" + std::to_string(m_mana.generic()) + ")"
                               : "";
        res += generic_str;
        res += mana::ManaBag::ManaToSymbols(m_mana.specific());
        return res;
    }

    [[nodiscard]] mana::ManaPrice ManaCost::getMana() const
    {
        return m_mana;
    }

    [[nodiscard]] bool ManaCost::canPay(
        [[maybe_unused]] const core::Card &source,
        const core::Player &player) const
    {
        return player.manaPool().canPay(m_mana);
    }

    void ManaCost::pay([[maybe_unused]] core::Game &game,
                       [[maybe_unused]] abilities::AbilityContext context) const
    {
        auto &player = game.getPlayer(context.controller_id);
        player.manaPool().pay(m_mana);
    }

} // namespace dandan::costs
