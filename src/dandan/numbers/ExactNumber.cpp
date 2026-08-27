
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace
{
    using namespace dandan::numbers;
    using namespace dandan::serialization;

    const auto registered = []
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

namespace dandan::numbers
{
    ExactNumber::ExactNumber(int value) : m_value(value)
    {
    }

    [[nodiscard]] int ExactNumber::getValue() const
    {
        return m_value;
    }

    [[nodiscard]] int ExactNumber::getValue(
        [[maybe_unused]] core::ExecutionContext exec_ctx,
        [[maybe_unused]] effects::EffectContext context) const
    {
        return m_value;
    }

    [[nodiscard]] std::unique_ptr<INumber> ExactNumber::clone() const
    {
        return std::make_unique<ExactNumber>(m_value);
    }
} // namespace dandan::numbers
