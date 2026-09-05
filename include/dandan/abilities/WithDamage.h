#ifndef WITHDAMAGE_H
#define WITHDAMAGE_H

#include "IAbilityDecorator.h"

namespace dandan::abilities
{
    /** @brief An ability decorator that adds self damage to an ability
     * @class WithDamage
     *
     * @implements IAbilityDecorator
     */
    class WithDamage final : public IAbilityDecorator
    {
    public:
        /** Constructor
         * the self damage amount is set to 1 by default
         * @param ability The ability to decorate
         */
        explicit WithDamage(std::unique_ptr<IAbility> ability);

        /** Constructor
         * @param ability The ability to decorate
         * @param damage The amount of damage to add
         */
        WithDamage(std::unique_ptr<IAbility> ability, int damage);

        [[nodiscard]] std::string display() const override;
        [[nodiscard]] std::string displayOption(size_t index) const override;

        /** Get the damage amount
         * @return The damage amount
         */
        [[nodiscard]] int getDamage() const;

        /** Check if the decorated ability applies to a given event and context.
         * @param event The event to check.
         * @param context The ability context.
         * @return True if the ability applies, false otherwise.
         */
        [[nodiscard]] bool appliesTo(const events::IEvent &event,
                                     abilities::AbilityContext context) const;

        [[nodiscard]] std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::ExecutionContext exec_ctx, AbilityContext context) const override;

    private:
        int m_damage{1};
    };
} // namespace dandan::abilities


#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace dandan::serialization::registration
{
    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::costs;
    using namespace dandan::mana;

    inline const auto registeredWithDamage = []
    {
        AbilityRegistry::instance().registerType<WithDamage>(
            "WithDamage",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *with_damage{
                    dynamic_cast<const WithDamage *>(ability)};
                json["damage"] = with_damage->getDamage();
                json["ability"] = JsonFactory<IAbility>::create_json(
                    with_damage->getInnerAbility());
                return json;
            },
            [](const nlohmann::json &json)
            {
                const int damage{json.at("damage").get<int>()};
                auto inner_ability =
                    JsonFactory<IAbility>::create_product(json.at("ability"));
                return std::make_unique<WithDamage>(std::move(inner_ability),
                                                    damage);
            });

        return true;
    }();
} // namespace
#endif

#endif
