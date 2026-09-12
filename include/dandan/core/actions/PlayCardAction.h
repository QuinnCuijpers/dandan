#ifndef DANDAN_PLAYCARDACTION_H
#define DANDAN_PLAYCARDACTION_H

#include "dandan/core/CardID.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include "dandan/utils/strSplit.h"
#include <cassert>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

enum class CastMode : uint8_t
{
    Normal,
    Flashback,
};

inline CastMode CastModeFromStr(const std::string &str)
{
    if (str == "Flashback")
    {
        return CastMode::Flashback;
    }

    return CastMode::Normal;
}

struct CastRequest
{

    CastRequest(dandan::core::CardID card_id,
                std::optional<CastMode> mode = std::nullopt)
        : card_id(card_id), mode{mode.value_or(CastMode::Normal)}
    {
    }

    dandan::core::CardID card_id;
    CastMode mode = CastMode::Normal;

    static CastRequest fromStr(const std::string &input)
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
};

namespace dandan::core
{
    /**
     * @brief An action that represents playing a card.
     * @class PlayCardAction
     *
     * @implements IAction
     */
    class PlayCardAction : public IAction
    {
    public:
        /**
         * Constructs a new play card action.
         * @param req The cast request of the card to play.
         */
        explicit PlayCardAction(CastRequest req);

        /** Get the card ID of the card to play.
         * @return The card ID of the card to play.
         */
        [[nodiscard]] CardID getCardID() const;

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx) override;

    private:
        CastRequest m_cast_request;
    };
} // namespace dandan::core

#endif // DANDAN_PLAYCARDACTION_H
