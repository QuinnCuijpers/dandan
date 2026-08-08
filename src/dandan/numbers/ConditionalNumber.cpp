#include "dandan/numbers/ConditionalNumber.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"
#include "dandan/serialization/JsonTypeRegistry.h"

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonRegisterMacros.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::serialization;
    using namespace dandan::numbers;
    using namespace dandan::conditions;

    DANDAN_JSONREGISTER_NUMBER(
        ConditionalNumber, "conditionalNumber",
        [](const INumber *number)
        {
            auto json = nlohmann::json::object();
            const auto *condition_number{
                dynamic_cast<const ConditionalNumber *>(number)};
            json["ifNumber"] = JsonFactory<INumber>::create_json(
                condition_number->getIfNumber());
            json["elseNumber"] = JsonFactory<INumber>::create_json(
                condition_number->getElseNumber());
            json["condition"] = JsonFactory<ICondition>::create_json(
                condition_number->getCondition());
            return json;
        },
        [](const nlohmann::json &data)
        {
            auto condition{
                JsonFactory<ICondition>::create_product(data.at("condition"))};

            auto if_{JsonFactory<INumber>::create_product(data.at("ifNumber"))};

            auto else_{
                JsonFactory<INumber>::create_product(data.at("elseNumber"))};

            return std::make_unique<ConditionalNumber>(
                std::move(if_), std::move(else_), std::move(condition));
        },
        JsonRepresentation::TAGGED);
} // namespace
#endif

namespace dandan::numbers
{

    ConditionalNumber::ConditionalNumber(
        std::unique_ptr<INumber> if_, std::unique_ptr<INumber> else_,
        std::unique_ptr<conditions::ICondition> condition)
        : m_if_number{std::move(if_)}, m_else_number(std::move(else_)),
          m_condition{std::move(condition)}
    {
    }

    ConditionalNumber::ConditionalNumber(
        int if_, int else_, std::unique_ptr<conditions::ICondition> condition)
        : m_if_number{std::make_unique<ExactNumber>(if_)},
          m_else_number(std::make_unique<ExactNumber>(else_)),
          m_condition{std::move(condition)}
    {
    }

    int ConditionalNumber::getValue(core::Game &game,
                                    effects::EffectContext context) const
    {
        if (m_condition->isSatisfied(game, context))
        {
            return m_if_number->getValue(game, context);
        }

        return m_else_number->getValue(game, context);
    }

    [[nodiscard]] std::unique_ptr<INumber> ConditionalNumber::clone() const
    {
        return std::make_unique<ConditionalNumber>(
            m_if_number->clone(), m_else_number->clone(), m_condition->clone());
    }

    [[nodiscard]] const INumber *ConditionalNumber::getIfNumber() const
    {
        return m_if_number.get();
    }

    [[nodiscard]] const INumber *ConditionalNumber::getElseNumber() const
    {
        return m_else_number.get();
    }

    [[nodiscard]] const conditions::ICondition *ConditionalNumber::
        getCondition() const
    {
        return m_condition.get();
    }

} // namespace dandan::numbers
