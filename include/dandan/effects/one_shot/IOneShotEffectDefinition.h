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
namespace dandan::effects
{
    using links = std::vector<std::string>;

    class IOneShotEffectDefinition
    {
    public:
        IOneShotEffectDefinition(
            std::optional<links> read_links = std::nullopt,
            std::optional<links> write_links = std::nullopt)
            : m_write_links(std::move(write_links)),
              m_read_links(std::move(read_links))
        {
        }

        IOneShotEffectDefinition(const IOneShotEffectDefinition &) = delete;
        IOneShotEffectDefinition(IOneShotEffectDefinition &&) = delete;
        IOneShotEffectDefinition &operator=(const IOneShotEffectDefinition &) =
            delete;
        IOneShotEffectDefinition &operator=(IOneShotEffectDefinition &&) =
            delete;
        virtual ~IOneShotEffectDefinition() = default;

        [[nodiscard]] virtual std::unique_ptr<IOneShotEffect> bind(
            const core::Game &game, EffectContext context) const = 0;

        [[nodiscard]] virtual std::string display() const
        {
            throw std::runtime_error("Unimplemented display for definition");
        }

        [[nodiscard]] virtual std::unique_ptr<IOneShotEffectDefinition> clone()
            const = 0;

        [[nodiscard]] virtual const core::TargetRequirement *
        getTargetRequirement() const
        {
            return nullptr;
        }

        [[nodiscard]] const std::optional<links> &writeLinks() const
        {
            return m_write_links;
        }

        [[nodiscard]] const std::optional<links> &readLinks() const
        {
            return m_read_links;
        }

        void addReadLink(const std::string &key)
        {
            if (m_read_links.has_value())
            {
                m_read_links->emplace_back(key);
            }
            else
            {
                m_read_links = {key};
            }
        }

        void addWriteLink(const std::string &key)
        {
            if (m_write_links.has_value())
            {
                m_write_links->emplace_back(key);
            }
            else
            {
                m_write_links = {key};
            }
        }

        [[nodiscard]] core::ExpireTime expires() const
        {
            return m_expires;
        }

        void addExpireTime(core::ExpireTime expire_time)
        {
            m_expires = expire_time;
        }

    private:
        std::optional<links> m_write_links;
        std::optional<links> m_read_links;
        core::ExpireTime m_expires{core::ExpireTime::None};
    };
} // namespace dandan::effects

#endif