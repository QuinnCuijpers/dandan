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
    /** @brief The ways a card can be cast. */
    enum class CastMode : uint8_t
    {
        /// Cast from hand for its normal cost.
        Normal,
        /// Cast from the graveyard using flashback.
        Flashback,
    };

    /** Parses a cast mode from a string.
     * @param str The string to parse.
     * @return The parsed cast mode.
     */
    CastMode CastModeFromStr(const std::string &str);

    /** @brief A request to cast a card.
     * @struct CastRequest
     */
    struct CastRequest
    {

        /** Constructs a cast request.
         * @param card_id The ID of the card to cast.
         * @param mode The optional cast mode.
         */
        explicit CastRequest(dandan::core::CardID card_id,
                             std::optional<CastMode> mode = std::nullopt);

        /// The ID of the card to cast.
        dandan::core::CardID card_id;
        /// The mode used to cast the card.
        CastMode mode = CastMode::Normal;

        /** Parses a cast request from an input string.
         * @param input The input string to parse.
         * @return The parsed cast request.
         */
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

        /** Creates the effect that casts the requested card.
         * @param exec_ctx The execution context.
         * @return The effect that casts the card.
         */
        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx) override;

    private:
        CastRequest m_cast_request;
    };
} // namespace dandan::core

#endif // DANDAN_PLAYCARDACTION_H
