#ifndef DANDAN_IACTION_H
#define DANDAN_IACTION_H

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

        virtual void execute() = 0;
    };
} // namespace dandan::core

#endif