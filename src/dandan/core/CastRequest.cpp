
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/utils/strSplit.h"

namespace dandan::core
{

    CastRequest CastRequest::fromStr(const std::string &input)
    {
        auto parts = strSplit(input);
        assert(parts[0] == "play");
        auto card_id{dandan::core::CardID::fromInt(std::stoi(parts[1]))};

        std::optional<CastMode> mode{std::nullopt};

        for (size_t pos{}; pos < parts.size(); ++pos)
        {
            mode = CastModeFromStr(parts[pos]);
        }

        return {card_id, mode};
    };
} // namespace dandan::core
