#ifndef DANDAN_MATCHESREADLINKSCONDITION_H
#define DANDAN_MATCHESREADLINKSCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <cassert>
#include <memory>

namespace dandan::conditions
{
    /** @brief Checks whether two remembered link values are equal.
     * @class MatchesReadLinksCondition
     */
    class MatchesReadLinksCondition : public ICondition
    {

    public:
        /** Constructs a condition comparing two remembered values.
         * @param first The key of the first remembered value.
         * @param second The key of the second remembered value.
         */
        MatchesReadLinksCondition(std::string first, std::string second);

        [[nodiscard]] bool isSatisfied(
            core::ExecutionContext exec_ctx,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;

        /** Gets the first remembered key.
         * @return A const reference to the first key.
         */
        [[nodiscard]] const std::string &getfirst() const;

        /** Gets the second remembered key.
         * @return A const reference to the second key.
         */
        [[nodiscard]] const std::string &getSecond() const;

    private:
        std::string m_first;
        std::string m_second;
    };

} // namespace dandan::conditions


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;

    inline const auto registeredMatchesReadLinksCondition = []
    {
        ConditionRegistry::instance().registerType<MatchesReadLinksCondition>(
            "MatchesReadLinksCondition",
            [](const ICondition *condition)
            {
                auto json = nlohmann::json::object();
                const auto *matches{
                    dynamic_cast<const MatchesReadLinksCondition *>(condition),};
                json["first"] = matches->getfirst();
                json["second"] = matches->getSecond();
                return json;
            },
            [](const nlohmann::json &json)
            {
                auto first = json.at("first").get<std::string>();
                auto second = json.at("second").get<std::string>();
                return std::make_unique<MatchesReadLinksCondition>(first,
                                                                   second);
            });
        return true;
    }();
} // namespace
#endif

#endif
