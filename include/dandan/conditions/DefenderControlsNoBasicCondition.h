#ifndef DANDAN_DEFENDERCONTROLSNOBASICCONDITION_H
#define DANDAN_DEFENDERCONTROLSNOBASICCONDITION_H

#include "dandan/conditions/ICondition.h"
#include "dandan/core/Game.h"
#include "dandan/core/IMindBendable.h"
#include <memory>
#include <optional>
namespace dandan::conditions
{
    class DefenderControlsNoBasicCondition : public ICondition,
                                             public core::IMindBendable
    {

    public:
        explicit DefenderControlsNoBasicCondition(core::SubType type);

        [[nodiscard]] core::SubType type() const;

        [[nodiscard]] bool isSatisfied(
            core::ExecutionContext exec_ctx,
            std::optional<effects::EffectContext> context =
                std::nullopt) const override;

        [[nodiscard]] std::unique_ptr<ICondition> clone() const override
        {
            return std::make_unique<DefenderControlsNoBasicCondition>(m_type);
        }

        // NOLINTBEGIN(bugprone-easily-swappable-parameters)
        void replaceBasicWord(core::SubType from,
                              core::SubType new_basic) override;

        // NOLINTEND(bugprone-easily-swappable-parameters)

    private:
        core::SubType m_type;
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

    inline const auto registeredDefenderControlsNoBasicCondition = []
    {
        ConditionRegistry::instance()
            .registerType<DefenderControlsNoBasicCondition>(
                "DefenderControlsNoBasicCondition",
                [](const ICondition *condition)
                {
                    auto json = nlohmann::json::object();
                    const auto *defender_controls{
                        dynamic_cast<const DefenderControlsNoBasicCondition *>(
                            condition)};
                    json["type"] = defender_controls->type();
                    return json;
                },
                [](const nlohmann::json &json)
                {
                    auto type = json.at("type").get<dandan::core::SubType>();
                    return std::make_unique<DefenderControlsNoBasicCondition>(
                        type);
                });
        return true;
    }();
} // namespace
#endif

#endif
