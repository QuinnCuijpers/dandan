#ifndef DANDAN_PLAYCARDACTION_H
#define DANDAN_PLAYCARDACTION_H

#include "dandan/core/CardID.h"
#include "dandan/core/actions/IAction.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <cassert>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>

namespace dandan::core
{
    enum class CastMode : uint8_t
    {
        Normal,
        Flashback,
    };

    inline CastMode CastModeFromStr(const std::string &str)
    {
        if (str == "flashback")
        {
            return CastMode::Flashback;
        }

        return CastMode::Normal;
    }

    struct CastRequest
    {

        explicit CastRequest(dandan::core::CardID card_id,
                             std::optional<CastMode> mode = std::nullopt)
            : card_id(card_id), mode{mode.value_or(CastMode::Normal)}
        {
        }

        dandan::core::CardID card_id;
        CastMode mode = CastMode::Normal;

        static CastRequest fromStr(const std::string &input);
    };

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
