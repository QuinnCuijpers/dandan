#ifndef DANDAN_IACTION_H
#define DANDAN_IACTION_H

#include "dandan/core/actions/ActionActor.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <variant>
namespace dandan::core
{

    class Game;
    /**
     * @brief Base Interface class for actions
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

        /** Gets the actor performing the action.
         * @return The action actor. Defaults to monostate, which represents a
         * global action not associated with any particular card or player.
         */
        [[nodiscard]] virtual ActionActor getActor() const
        {
            return std::monostate{};
        }
    };
} // namespace dandan::core

#endif
