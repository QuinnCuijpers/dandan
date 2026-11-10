#include "dandan/effects/one_shot/EffectList.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace dandan::effects
{
    EffectList::EffectList(
        const std::vector<std::unique_ptr<IOneShotEffect>> &effects,
        EffectContext context)
        : IOneShotEffect(std::move(context))
    {
        std::transform(effects.begin(), effects.end(),
                       std::back_inserter(m_effects),
                       [](const auto &effect) { return effect->copy(); });
    }

    std::string EffectList::display() const
    {
        std::string result;
        for (const auto &effect : m_effects)
        {
            result += effect->display() + "\n";
        }
        return result;
    }

    std::unique_ptr<IOneShotEffect> EffectList::copy() const
    {
        std::vector<std::unique_ptr<IOneShotEffect>> cloned_effects;
        cloned_effects.reserve(m_effects.size());
        std::transform(m_effects.begin(), m_effects.end(),
                       std::back_inserter(cloned_effects),
                       [](const auto &effect) { return effect->copy(); });
        return std::make_unique<EffectList>(cloned_effects, getEffectContext());
    }

    std::unique_ptr<events::IEvent> EffectList::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &replacement_manager{exec_ctx.replacement_manager.get()};

        std::unique_ptr<events::IEvent> last_event{};
        for (const auto &effect : m_effects)
        {
            auto replaced_sub_effect{
                replacement_manager.applyReplacementEffects(*effect, exec_ctx),
            };
            last_event = replaced_sub_effect->apply(exec_ctx);
        }
        return last_event;
    }
} // namespace dandan::effects
