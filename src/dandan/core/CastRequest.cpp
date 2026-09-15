
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

        // the first two parts are the "play" keyword and the card id,
        // any remaining parts are cast-mode keywords
        for (size_t pos{2}; pos < parts.size(); ++pos)
        {
            mode = CastModeFromStr(parts[pos]);
        }

        return CastRequest(card_id, mode);
    };
} // namespace dandan::core
