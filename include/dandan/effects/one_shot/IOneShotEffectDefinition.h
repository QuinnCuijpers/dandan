#ifndef DANDAN_IONESHOTEFFECTDEFINITION_H
#define DANDAN_IONESHOTEFFECTDEFINITION_H

#include "dandan/core/Expire.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace dandan::core
{
    struct ExecutionContext;
}

namespace dandan::effects
{
    using links = std::vector<std::string>;

    /** @brief Base class for definitions that bind to concrete one-shot
     * effects.
     * @class IOneShotEffectDefinition
     */
    class IOneShotEffectDefinition
    {
    public:
        /** @brief Construct a definition with optional link keys.
         * @param read_links The link keys the effect reads, if any.
         * @param write_links The link keys the effect writes, if any.
         */
        explicit IOneShotEffectDefinition(
            std::optional<links> read_links = std::nullopt,
            std::optional<links> write_links = std::nullopt);

        IOneShotEffectDefinition(const IOneShotEffectDefinition &) = delete;
        IOneShotEffectDefinition(IOneShotEffectDefinition &&) = delete;
        IOneShotEffectDefinition &operator=(const IOneShotEffectDefinition &) =
            delete;
        IOneShotEffectDefinition &operator=(IOneShotEffectDefinition &&) =
            delete;
        virtual ~IOneShotEffectDefinition() = default;

        /** @brief Create a one-shot effect for the given execution context.
         * @param exec_ctx The execution context to bind in.
         * @param context The context of the effect to create.
         * @return The bound one-shot effect.
         */
        [[nodiscard]] virtual std::unique_ptr<IOneShotEffect> bind(
            core::ExecutionContext exec_ctx, EffectContext context) const = 0;

        /** @brief Get a human-readable description of the definition.
         * @return The display string.
         */
        [[nodiscard]] virtual std::string display() const;

        /** @brief Create a copy of this effect definition.
         * @return A unique pointer to the cloned definition.
         */
        [[nodiscard]] virtual std::unique_ptr<IOneShotEffectDefinition> clone()
            const = 0;

        /** @brief Get the targets required by this effect, if any.
         * @return The target requirement, or null if none is required.
         */
        [[nodiscard]] virtual const core::TargetRequirement *
        getTargetRequirement() const;

        /** @brief Get the link keys written by this effect.
         * @return The optional list of written link keys.
         */
        [[nodiscard]] const std::optional<links> &writeLinks() const;

        /** @brief Get the link keys read by this effect.
         * @return The optional list of read link keys.
         */
        [[nodiscard]] const std::optional<links> &readLinks() const;

        /** @brief Add a link key that this effect reads.
         * @param key The link key to add.
         */
        void addReadLink(const std::string &key);

        /** @brief Add a link key that this effect writes.
         * @param key The link key to add.
         */
        void addWriteLink(const std::string &key);

        /** @brief Get the time at which this effect expires.
         * @return The expiration time.
         */
        [[nodiscard]] core::ExpireTime expires() const;

        /** @brief Set the time at which this effect expires.
         * @param expire_time The expiration time to set.
         */
        void addExpireTime(core::ExpireTime expire_time);

    private:
        std::optional<links> m_write_links;
        std::optional<links> m_read_links;
        core::ExpireTime m_expires{core::ExpireTime::None};
    };
} // namespace dandan::effects

#endif
