#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/core/Card.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"

namespace dandan::effects
{
    std::unique_ptr<IOneShotEffect> ModalEffectDefinition::bind(
        const core::ExecutionContext exec_ctx, EffectContext context) const
    {
        auto &card_registry{exec_ctx.cards.get()};

        const auto *card{card_registry[context.card_id.value()]};
        std::cout << "Binding modal effect for card " << card->getData().name
                  << '\n';
        auto modal_choice{card->getModalChoice(*this)};
        return m_options.at(modal_choice)->bind(exec_ctx, context);
    }
} // namespace dandan::effects
