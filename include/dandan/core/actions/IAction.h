#ifndef DANDAN_IACTION_H
#define DANDAN_IACTION_H

#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
namespace dandan::core
{
    class IAction
    {
    public:
        IAction() = default;
        IAction(const IAction &) = delete;
        IAction(IAction &&) = delete;
        IAction &operator=(const IAction &) = delete;
        IAction &operator=(IAction &&) = delete;
        virtual ~IAction() = default;

        virtual std::unique_ptr<effects::IOneShotEffect> execute() = 0;
    };
} // namespace dandan::core

#endif