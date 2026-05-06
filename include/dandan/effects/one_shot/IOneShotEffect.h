#ifndef DANDAN_I_EFFECT_H
#define DANDAN_I_EFFECT_H

#include "dandan/events/IEvent.h"
#include <memory>
namespace dandan::core
{
    class Game;
}

namespace dandan::effects
{
    // TODO: change `apply` to take in a `GameState` object and modify it
    // instead of just printing something to the console
    class IOneShotEffect
    {
    public:
        IOneShotEffect() = default;
        IOneShotEffect(const IOneShotEffect &) = delete;
        IOneShotEffect(IOneShotEffect &&) = delete;
        IOneShotEffect &operator=(const IOneShotEffect &) = delete;
        IOneShotEffect &operator=(IOneShotEffect &&) = delete;
        virtual ~IOneShotEffect() = default;
        virtual std::unique_ptr<events::IEvent> apply(core::Game &game) = 0;
    };

} // namespace dandan::effects

#endif