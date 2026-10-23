#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/core/Card.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

namespace dandan::effects
{
    ModalEffectDefinition::ModalEffectDefinition(
        std::vector<std::unique_ptr<IOneShotEffectDefinition>> options)
        : m_options(std::move(options))
    {
    }

    std::string ModalEffectDefinition::display() const
    {
        std::string result = "Choose one -\n";
        for (const auto &m_option : m_options)
        {
            result += "* " + m_option->display() + "\n";
        }
        return result;
    }

    std::unique_ptr<IOneShotEffectDefinition> ModalEffectDefinition::clone()
        const
    {
        auto cloned_options{
            std::vector<std::unique_ptr<IOneShotEffectDefinition>>{}};

        std::transform(m_options.begin(), m_options.end(),
                       std::back_inserter(cloned_options),
                       [](const auto &option) { return option->clone(); });
        return std::make_unique<ModalEffectDefinition>(
            std::move(cloned_options));
    }

    const std::vector<std::unique_ptr<IOneShotEffectDefinition>> &
    ModalEffectDefinition::getOptions() const
    {
        return m_options;
    }

    std::unique_ptr<IOneShotEffect> ModalEffectDefinition::bind(
        const core::ExecutionContext exec_ctx, EffectContext context) const
    {
        const auto &card_registry{exec_ctx.cards.get()};

        const auto *card{card_registry.get(context.card_id)};
        std::cout << "Binding modal effect for card " << card->getData().name
                  << '\n';
        auto modal_choice{card->getModalChoice(*this)};
        return m_options.at(modal_choice)->bind(exec_ctx, context);
    }
} // namespace dandan::effects
