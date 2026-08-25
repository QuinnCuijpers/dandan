#ifndef DANDAN_MATCHESREADLINKSCONDITION_H
#define DANDAN_MATCHESREADLINKSCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include <cassert>
#include <memory>

namespace dandan::conditions
{
    class MatchesReadLinksCondition : public ICondition
    {

    public:
        MatchesReadLinksCondition(std::string first, std::string second);

        [[nodiscard]] bool isSatisfied(
            core::ExecutionContext exec_ctx,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;

        [[nodiscard]] const std::string &getfirst() const;

        [[nodiscard]] const std::string &getSecond() const;

    private:
        std::string m_first;
        std::string m_second;
    };

} // namespace dandan::conditions

#endif
