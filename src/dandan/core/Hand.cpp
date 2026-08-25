#include "dandan/core/Hand.h"
#include "dandan/core/Game.h"

namespace dandan::core
{
    void Hand::discardCard(CardID card_id, ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};
        const auto &card_registry{exec_ctx.cards.get()};

        auto *card = card_registry[card_id];
        std::cout << "Discarding card " << card->getData().name << '\n';
        removeCard(*card);
        game.graveyard().addCard(*card);
    }
} // namespace dandan::core
