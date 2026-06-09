#ifndef DANDAN_EFFECT_LIST_H
#define DANDAN_EFFECT_LIST_H

#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace dandan::effects
{
    /** @brief A list of one-shot effects.
     * @class EffectList
     */
    class EffectList : public IOneShotEffect
    {
    public:
        /** @brief Construct an EffectList with a vector of one-shot effects.
         * @param effects The vector of one-shot effects.
         */
        explicit EffectList(
            const std::vector<std::unique_ptr<IOneShotEffect>> &effects)
        {
            std::transform(effects.begin(), effects.end(),
                           std::back_inserter(m_effects),
                           [](const auto &effect) { return effect->copy(); });
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

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override
        {
            std::vector<std::unique_ptr<IOneShotEffect>> cloned_effects;
            cloned_effects.reserve(m_effects.size());
            std::transform(m_effects.begin(), m_effects.end(),
                           std::back_inserter(cloned_effects),
                           [](const auto &effect) { return effect->copy(); });
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