#ifndef DANDAN_IACTION_H
#define DANDAN_IACTION_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
namespace dandan::core
{

    class Game;
    /**
     * @brief Base interface for actions
     * @class IAction
     */
    class IAction
    {
    public:
        IAction() = default;
        IAction(const IAction &) = delete;
        IAction(IAction &&) = delete;
        IAction &operator=(const IAction &) = delete;
        IAction &operator=(IAction &&) = delete;
        virtual ~IAction() = default;

        /**
         * Creates an effect associated with this action.
         * @param game The game instance to use when creating the effect.
         * @return A unique pointer to the created effect.
         */
        virtual std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game) = 0;
    };
} // namespace dandan::core

#endif
