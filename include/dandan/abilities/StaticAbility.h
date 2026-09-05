#ifndef REPLACEMENTABILITY_H
#define REPLACEMENTABILITY_H

#include "IAbility.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/effects/continuous/IContinuousEffect.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <cstdint>
#include <memory>

namespace dandan::abilities
{

    /** @brief A static ability that modifies the game state
     * @class StaticAbility
     *
     * @implements IAbility
     */
    class StaticAbility final : public IAbility
    {
    public:
        /** The type of the static ability
         * @enum Type
         */
        enum class Type : uint8_t
        {
            /// A characteristic-defining ability modifies the characteristics
            /// of a card
            CharacteristicDefining,
            /// A static ability that modifies the rules of the game, such as
            /// "Players can't gain life"
            Prevention,
            /// A static ability that modifies effects
            Replacement,
        };

        /** Constructor *@param type The type of the static ability
         *@param effect The continuous effect of the static ability
         */
        StaticAbility(Type type,
                      std::unique_ptr<effects::IContinuousEffect> effect);

        /** Get the type of the static ability
         * @return The type of the static ability
         */
        [[nodiscard]] Type getType() const;

        /** Get the effect of the static ability
         * @return The effect of the static ability
         */
        [[nodiscard]] const effects::IContinuousEffect *getEffect() const;

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx,
            AbilityContext context) const override;

    private:
        Type m_type{};
        std::unique_ptr<effects::IContinuousEffect> m_effect;
    };
} // namespace dandan::abilities

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>

namespace dandan::abilities
{
    NLOHMANN_JSON_SERIALIZE_ENUM( // NOLINT
        StaticAbility::Type,
        {{StaticAbility::Type::CharacteristicDefining,
          "CharacteristicDefining"},
         {StaticAbility::Type::Prevention, "Prevention"},
         {StaticAbility::Type::Replacement, "Replacement"}});
}

namespace dandan::serialization::registration
{
    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::costs;
    using namespace dandan::mana;
    using namespace dandan::effects;

    inline const auto registeredStaticAbility = []
    {
        AbilityRegistry::instance().registerType<StaticAbility>(
            "StaticAbility",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *static_ability{
                    dynamic_cast<const StaticAbility *>(ability)};

                json["static_type"] = static_ability->getType();

                json["continuous_effect"] =
                    JsonFactory<IContinuousEffect>::create_json(
                        static_ability->getEffect());
                return json;
            },
            [](const nlohmann::json &json)
            {
                auto static_type{
                    json.at("static_type").get<StaticAbility::Type>()};

                auto continuous_effect{
                    JsonFactory<IContinuousEffect>::create_product(
                        json.at("continuous_effect"))};

                return std::make_unique<StaticAbility>(
                    static_type, std::move(continuous_effect));
            });

        return true;
    }();
} // namespace dandan::serialization::registration
#endif

#endif // REPLACEMENTABILITY_H
