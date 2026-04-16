#ifndef DANDAN_I_COST
#define DANDAN_I_COST

namespace dandan::costs
{
    class ICost
    {
    public:
        virtual ~ICost() = default;
        virtual void evaluate() = 0;
    };
} // namespace dandan::costs

#endif