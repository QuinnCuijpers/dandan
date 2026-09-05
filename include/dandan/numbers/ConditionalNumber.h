#ifndef DANDAN_CONDITIONALNUMBER_H
#define DANDAN_CONDITIONALNUMBER_H

#include "dandan/conditions/ICondition.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/numbers/ExactNumber.h"
#include "dandan/numbers/INumber.h"
#include <memory>

namespace dandan::numbers
{
    class ConditionalNumber : public INumber
    {

    public:
        ConditionalNumber(std::unique_ptr<INumber> if_,
                          std::unique_ptr<INumber> else_,
                          std::unique_ptr<conditions::ICondition> condition);

        ConditionalNumber(int if_, int else_,
                          std::unique_ptr<conditions::ICondition> condition);

        [[nodiscard]] int getValue(
            core::ExecutionContext exec_ctx,
            effects::EffectContext context) const override;

        [[nodiscard]] std::unique_ptr<INumber> clone() const override;

        [[nodiscard]] const INumber *getIfNumber() const;

        [[nodiscard]] const INumber *getElseNumber() const;

        [[nodiscard]] const conditions::ICondition *getCondition() const;

    private:
        std::unique_ptr<INumber> m_if_number;
        std::unique_ptr<INumber> m_else_number;
        std::unique_ptr<conditions::ICondition> m_condition;
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
    using namespace dandan::conditions;

    inline const auto registeredConditionalNumber = []
    {
        NumberRegistry::instance().registerType<ConditionalNumber>(
            "ConditionalNumber",
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
                auto condition{JsonFactory<ICondition>::create_product(
                    data.at("condition"))};

                auto if_ = data["ifNumber"].is_number()
                               ? std::make_unique<ExactNumber>(
                                     data["ifNumber"].get<int>())
                               : JsonFactory<INumber>::create_product(
                                     data["ifNumber"]);

                auto else_ = data["elseNumber"].is_number()
                                 ? std::make_unique<ExactNumber>(
                                       data["elseNumber"].get<int>())
                                 : JsonFactory<INumber>::create_product(
                                       data["elseNumber"]);

                return std::make_unique<ConditionalNumber>(
                    std::move(if_), std::move(else_), std::move(condition));
            });
        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif
