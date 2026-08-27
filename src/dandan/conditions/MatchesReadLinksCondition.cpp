#include "dandan/conditions/MatchesReadLinksCondition.h"
#include <string>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;

    const auto registered = []
    {
        ConditionRegistry::instance().registerType<MatchesReadLinksCondition>(
            "MatchesReadLinksCondition",
            [](const ICondition *condition)
            {
                auto json = nlohmann::json::object();
                const auto *matches{
                    dynamic_cast<const MatchesReadLinksCondition *>(condition)};
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

namespace dandan::conditions
{
    MatchesReadLinksCondition::MatchesReadLinksCondition(std::string first,
                                                         std::string second)
        : m_first(std::move(first)), m_second(std::move(second))
    {
    }

    [[nodiscard]] bool MatchesReadLinksCondition::isSatisfied(
        const core::ExecutionContext exec_ctx,
        std::optional<effects::EffectContext> context) const
    {

        auto &card_registry{exec_ctx.cards.get()};

        assert(context.has_value() &&
               "Effect with Matches Read Links Condition tried checking "
               "without a context and thus no source card");
        auto card_id{context->card_id.value()};
        const auto *card{card_registry[card_id]};
        auto links{card->linkMap()};
        std::cout << m_first << '\n';
        std::cout << m_second << '\n';
        return links.at(m_first) == links.at(m_second);
    }

    [[nodiscard]] std::unique_ptr<ICondition> MatchesReadLinksCondition::clone()
        const
    {
        return std::make_unique<MatchesReadLinksCondition>(m_first, m_second);
    }

    [[nodiscard]] const std::string &MatchesReadLinksCondition::getfirst() const
    {
        return m_first;
    }

    [[nodiscard]] const std::string &MatchesReadLinksCondition::getSecond()
        const
    {
        return m_second;
    }

} // namespace dandan::conditions
