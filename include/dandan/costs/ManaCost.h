#ifndef DANDAN_MANACOST_H
#define DANDAN_MANACOST_H

#include "ICost.h"
#include "dandan/core/Game.h"
#include "dandan/mana/Mana.h"
#include <memory>

namespace dandan::costs
{
    class ManaCost : public ICost
    {
    public:
        explicit ManaCost(std::unique_ptr<mana::Mana> mana)
            : m_mana{std::move(mana)} {};

        [[nodiscard]] mana::Mana *getMana() const
        {
            return m_mana.get();
        }

        [[nodiscard]] bool canPay([[maybe_unused]] const core::Card &source,
                                  const core::Player &player) const override
        {
            return player.manaPool().canPay(*m_mana);
        }

        void pay(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] abilities::AbilityContext context) const override
        {
            auto &player = game.getPlayer(context.controller_id);
            player.manaPool().pay(*m_mana);
        }

    private:
        std::unique_ptr<mana::Mana> m_mana;
    };
} // namespace dandan::costs

#endif