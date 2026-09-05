#ifndef DANDAN_EXACTNUMBER_H
#define DANDAN_EXACTNUMBER_H

#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/INumber.h"

namespace dandan::numbers
{
    class ExactNumber : public INumber
    {
    public:
        explicit ExactNumber(int value);

        [[nodiscard]] int getValue() const;

        [[nodiscard]] int getValue(
            core::ExecutionContext exec_ctx, effects::EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<INumber> clone() const override;

    private:
        int m_value;
    };
} // namespace dandan::numbers


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::serialization::registration
{
    using namespace dandan::numbers;
    using namespace dandan::serialization;

    inline const auto registeredExactNumber = []
    {
        NumberRegistry::instance().registerType<ExactNumber>(
            "ExactNumber",
            [](const INumber *number)
            {
                const auto *exact{dynamic_cast<const ExactNumber *>(number)};
                return nlohmann::json(exact->getValue());
            },
            [](const nlohmann::json &json)
            {
                int value = json.at("value").get<int>();
                return std::make_unique<ExactNumber>(value);
            },
            JsonRepresentation::INLINE);
        return true;
    }();

} // namespace
#endif

#endif
