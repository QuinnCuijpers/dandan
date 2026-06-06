#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/core/Game.h"
#include <optional>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> IOneShotEffect::apply(
        core::Game &game) const
    {
        auto event = apply_impl(game);
        game.conditionManager().checkConditions(game);

        auto next = getNext();
        if (next == std::nullopt)
        {
            std::cout << "No next effect in chain found for "
                      << typeid(*this).name() << "\n";
            return event;
        }

        auto current = std::move(next);

        while (current.has_value())
        {
            auto *current_effect = current.value().get();
            std::cout << "Applying next effect in chain\n";
            current_effect->apply_impl(game);
            game.conditionManager().checkConditions(game);
            auto next = current_effect->getNext();
            current = std::move(next);
        }

        return event;
    }

} // namespace dandan::effects