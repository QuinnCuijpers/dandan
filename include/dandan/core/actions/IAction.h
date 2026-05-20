#ifndef DANDAN_IACTION_H
#define DANDAN_IACTION_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
namespace dandan::core
{
    /**
     * Base interface for actions
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
         * @return A unique pointer to the created effect.
         */
        virtual std::unique_ptr<effects::IOneShotEffect> createEffect() = 0;
    };
} // namespace dandan::core

#endif