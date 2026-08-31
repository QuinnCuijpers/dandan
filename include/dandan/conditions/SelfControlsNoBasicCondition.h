#ifndef DANDAN_SELFCONTROLSNObasicCONDITION_H
#define DANDAN_SELFCONTROLSNObasicCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include "dandan/core/IMindBendable.h"
#include <memory>

namespace dandan::conditions
{
    /**
     * @brief A condition that checks if the player controls no island.
     * @class ControlsNoIslandCondition
     *
     * @implements ICondition
     */
    class SelfControlsNoBasicCondition : public ICondition, core::IMindBendable
    {
    public:
        explicit SelfControlsNoBasicCondition(core::SubType basic_land_type);

        [[nodiscard]] core::SubType type() const;

        [[nodiscard]] bool isSatisfied(
            core::ExecutionContext exec_ctx,
            std::optional<effects::EffectContext> context) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override;

        // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        void replaceBasicWord(core::SubType from,
                              core::SubType new_basic) override;
        // NOLINTEND(bugprone-easily-swappable-parameters)

    private:
        core::SubType m_basic_type;
    };
} // namespace dandan::conditions


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonEnums.h" // IWYU pragma: keep
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::conditions;
    using namespace dandan::serialization;

    inline const auto registeredSelfControlsNoBasicCondition = []
    {
        ConditionRegistry::instance()
            .registerType<SelfControlsNoBasicCondition>(
                "SelfControlsNoBasicCondition",
                [](const ICondition *condition)
                {
                    auto json = nlohmann::json::object();
                    const auto *self_controls{
                        dynamic_cast<const SelfControlsNoBasicCondition *>(
                            condition)};
                    json["type"] = self_controls->type();
                    return json;
                },
                [](const nlohmann::json &json)
                {
                    auto type = json.at("type").get<dandan::core::SubType>();
                    return std::make_unique<SelfControlsNoBasicCondition>(type);
                });
        return true;
    }();
} // namespace
#endif

#endif
