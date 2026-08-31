#include "dandan/conditions/MatchesReadLinksCondition.h"
#include <string>

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
