#ifndef DANDAN_EFFECT_LIST_H
#define DANDAN_EFFECT_LIST_H

#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <vector>

namespace dandan::effects
{
    class EffectList : public IOneShotEffect
    {
    public:
        EffectList(const std::vector<std::unique_ptr<IOneShotEffect>> &effects)
        {
            for (const auto &effect : effects)
            {
                m_effects.push_back(effect->clone());
            }
        }

        [[nodiscard]] std::string display() const override
        {
            std::string result;
            for (const auto &effect : m_effects)
            {
                result += effect->display() + "\n";
            }
            return result;
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> clone() const override
        {
            std::vector<std::unique_ptr<IOneShotEffect>> cloned_effects;
            cloned_effects.reserve(m_effects.size());
            for (const auto &effect : m_effects)
            {
                cloned_effects.push_back(effect->clone());
            }
            return std::make_unique<EffectList>(cloned_effects);
        }

        // TODO: impl an event bus instead of pushing the last event
        std::unique_ptr<events::IEvent> apply_impl(
            core::Game &game) const override
        {
            std::unique_ptr<events::IEvent> last_event{};
            for (const auto &effect : m_effects)
            {
                auto replaced_sub_effect{
                    game.replacementManager().applyReplacementEffects(*effect,
                                                                      game)};
                last_event = replaced_sub_effect->apply(game);
            }
            return last_event;
        }

    private:
        std::vector<std::unique_ptr<IOneShotEffect>> m_effects;
    };
} // namespace dandan::effects

#endif