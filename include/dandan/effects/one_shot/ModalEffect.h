#ifndef DANDAN_MODAL_EFFECT_H
#define DANDAN_MODAL_EFFECT_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace dandan::effects
{

    class ModalEffectDefinition : public IOneShotEffectDefinition
    {

    public:
        explicit ModalEffectDefinition(
            std::vector<std::unique_ptr<IOneShotEffectDefinition>> options)
            : m_options(std::move(options))
        {
        }

        [[nodiscard]] std::string display() const override
        {
            std::string result = "Choose one -\n";
            for (const auto &m_option : m_options)
            {
                result += "* " + m_option->display() + "\n";
            }
            return result;
        }

        [[nodiscard]] std::unique_ptr<IOneShotEffect> bind(
            const core::Game &game, EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<IOneShotEffectDefinition> clone()
            const override
        {
            auto cloned_options{
                std::vector<std::unique_ptr<IOneShotEffectDefinition>>{}};

            std::transform(m_options.begin(), m_options.end(),
                           std::back_inserter(cloned_options),
                           [](const auto &option) { return option->clone(); });
            return std::make_unique<ModalEffectDefinition>(
                std::move(cloned_options));
        }

        [[nodiscard]] const std::vector<
            std::unique_ptr<IOneShotEffectDefinition>> &
        getOptions() const
        {
            return m_options;
        }

    private:
        std::vector<std::unique_ptr<IOneShotEffectDefinition>> m_options;
    };
} // namespace dandan::effects

#endif