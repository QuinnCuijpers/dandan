#ifndef DANDAN_EFFECT_LIST_H
#define DANDAN_EFFECT_LIST_H

#include "dandan/core/ExecutionContext.h"
#include "dandan/core/engine/ReplacementManager.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <algorithm>
#include <memory>
#include <utility>
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
            const std::vector<std::unique_ptr<IOneShotEffect>> &effects,
            EffectContext context);

        [[nodiscard]] std::string display() const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffect> copy() const override;

        // TODO: impl an event bus instead of pushing the last event
        [[nodiscard]] std::unique_ptr<events::IEvent> apply_impl(
            core::ExecutionContext exec_ctx) const override
        {
            auto &replacement_manager{exec_ctx.replacement_manager.get()};

            std::unique_ptr<events::IEvent> last_event{};
            for (const auto &effect : m_effects)
            {
                auto replaced_sub_effect{
                    replacement_manager.applyReplacementEffects(*effect,
                                                                exec_ctx)};
                last_event = replaced_sub_effect->apply(exec_ctx);
            }
            return last_event;
        }

    private:
        std::vector<std::unique_ptr<IOneShotEffect>> m_effects;
    };
} // namespace dandan::effects

#endif
