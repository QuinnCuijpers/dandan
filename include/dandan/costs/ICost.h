#ifndef DANDAN_I_COST
#define DANDAN_I_COST

namespace dandan::costs
{
    class ICost
    {
    public:
        ICost() = default;
        ICost(const ICost &) = default;
        ICost(ICost &&) = delete;
        ICost &operator=(const ICost &) = default;
        ICost &operator=(ICost &&) = delete;
        virtual ~ICost() = default;
        virtual void evaluate() = 0;
    };
} // namespace dandan::costs

#endif