#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/core/Expire.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/effects/EffectContext.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace dandan::effects
{
    IOneShotEffectDefinition::IOneShotEffectDefinition(
        std::optional<links> read_links, std::optional<links> write_links)
        : m_write_links(std::move(write_links)),
          m_read_links(std::move(read_links))
    {
    }

    std::string IOneShotEffectDefinition::display() const
    {
        throw std::runtime_error("Unimplemented display for definition");
    }

    const core::TargetRequirement *IOneShotEffectDefinition::
        getTargetRequirement() const
    {
        return nullptr;
    }

    const std::optional<links> &IOneShotEffectDefinition::writeLinks() const
    {
        return m_write_links;
    }

    const std::optional<links> &IOneShotEffectDefinition::readLinks() const
    {
        return m_read_links;
    }

    core::ExpireTime IOneShotEffectDefinition::expires() const
    {
        return m_expires;
    }
} // namespace dandan::effects
