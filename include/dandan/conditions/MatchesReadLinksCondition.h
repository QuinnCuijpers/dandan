#ifndef DANDAN_MATCHESREADLINKSCONDITION_H
#define DANDAN_MATCHESREADLINKSCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

namespace dandan::conditions
{
    class MatchesReadLinksCondition : public ICondition
    {

    public:
        MatchesReadLinksCondition(std::string first, std::string second)
            : m_first(std::move(first)), m_second(std::move(second))
        {
        }

        [[nodiscard]] bool isSatisfied(
            const core::Game &game,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override
        {
            assert(context.has_value() &&
                   "Effect with Matches Read Links Condition tried checking "
                   "without a context and thus no source card");
            auto card_id{context->card_id.value()};
            const auto *card{game.getCardByID(card_id)};
            auto links{card->linkMap()};
            std::cout << m_first << '\n';
            std::cout << m_second << '\n';
            return links.at(m_first) == links.at(m_second);
        }

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override
        {
            return std::make_unique<MatchesReadLinksCondition>(m_first,
                                                               m_second);
        }

        [[nodiscard]] const std::string &getfirst() const
        {
            return m_first;
        }

        [[nodiscard]] const std::string &getSecond() const
        {
            return m_second;
        }

    private:
        std::string m_first;
        std::string m_second;
    };

} // namespace dandan::conditions

#endif