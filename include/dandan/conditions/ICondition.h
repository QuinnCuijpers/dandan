#ifndef DANDAN_ICONDITION_H
#define DANDAN_ICONDITION_H

namespace dandan::conditions
{

    class ICondition
    {
    public:
        ICondition() = default;
        ICondition(const ICondition &) = delete;
        ICondition(ICondition &&) = delete;
        ICondition &operator=(const ICondition &) = delete;
        ICondition &operator=(ICondition &&) = delete;
        virtual ~ICondition() = default;

        virtual bool isSatisfied() = 0;
    };

} // namespace dandan::conditions
#endif