#include "dandan/effects/one_shot/ModalEffect.h"
#include "dandan/core/Game.h"

namespace dandan::effects
{
    std::unique_ptr<IOneShotEffect> ModalEffectDefinition::bind(
        const core::Game &game, EffectContext context) const
    {
        const auto *card{game.getCardByID(context.card_id.value())};
        std::cout << "Binding modal effect for card "
                  << card->getData().getName() << '\n';
        auto modal_choice{card->getModalChoice(*this)};
        return m_options.at(modal_choice)->bind(game, context);
    }
} // namespace dandan::effects