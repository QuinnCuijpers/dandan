#ifndef DANDAN_GENERICMANACOST_H
#define DANDAN_GENERICMANACOST_H

#include "ICost.h"

namespace dandan::costs
{
    class GenericManaCost : public ICost
    {
    public:
        explicit GenericManaCost(int amount) : m_amount{amount} {}

        void from_json(const nlohmann::json &j, ICost &cost) override;
        void to_json(nlohmann::json &j, const ICost &cost) override;
        void evaluate() override;

    private:
        int m_amount{0};
    };
}

#endif