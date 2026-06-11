#ifndef DANDAN_MILL_EFFECT_H
#define DANDAN_MILL_EFFECT_H

#include "dandan/core/Constants.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <memory>

namespace dandan::effects
{
    class MillEffect : public IOneShotEffect
    {
    public:
        MillEffect(int amount, core::PlayerID player_id)
            : m_amount(amount), m_player_id(player_id)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            return std::make_unique<MillEffect>(m_amount, m_player_id);
        }

        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override;

    private:
        int m_amount;
        core::PlayerID m_player_id;
    };

    class MillEffectDefinition : public IOneShotEffectDefinition
    {
    public:
        MillEffectDefinition(int amount) : m_amount(amount)
        {
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            core::Game &game,
            [[maybe_unused]] EffectContext context) const override
        {
            std::cout << "Which player do you want to mill? (0-"
                      << core::AMOUNT_PLAYERS - 1 << "): ";
            std::string input;
            std::getline(game.istream(), input);
            int player_choice = std::stoi(input);
            if (player_choice < 0 ||
                player_choice >= static_cast<int>(core::AMOUNT_PLAYERS))
            {
                throw std::runtime_error(
                    "Invalid player choice for mill effect");
            }
            return std::make_unique<MillEffect>(
                m_amount, core::PlayerID::fromInt(player_choice));
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            return std::make_unique<MillEffectDefinition>(m_amount);
        }

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] int getAmount() const
        {
            return m_amount;
        }

    private:
        int m_amount;
    };
} // namespace dandan::effects

#endif