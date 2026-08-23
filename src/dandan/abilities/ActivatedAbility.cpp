#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/IOneShotEffect.h"
#include <iostream>
#include <memory>

#ifdef DANDAN_SERIALIZE
#include "dandan/serialization/JsonFactory.h"
#include "dandan/serialization/JsonTypeRegistry.h"
#include <nlohmann/json.hpp>
namespace
{
    using namespace dandan::abilities;
    using namespace dandan::serialization;
    using namespace dandan::costs;
    using namespace dandan::effects;

    const auto registered = []
    {
        AbilityRegistry::instance().registerType<ActivatedAbility>(
            "ActivatedAbility",
            [](const IAbility *ability)
            {
                auto json = nlohmann::json::object();
                const auto *activated{
                    dynamic_cast<const ActivatedAbility *>(ability)};
                json["cost"] =
                    JsonFactory<ICost>::create_json(activated->getCost());
                json["effect"] =
                    JsonFactory<IOneShotEffectDefinition>::create_json(
                        activated->getEffect());
                return json;
            },
            [](const nlohmann::json &json)
            {
                auto cost{JsonFactory<ICost>::create_product(json.at("cost"))};

                auto effect{
                    JsonFactory<IOneShotEffectDefinition>::create_product(
                        json.at("effect"))};
                return std::make_unique<ActivatedAbility>(std::move(cost),
                                                          std::move(effect));
            });
        return true;
    }();
} // namespace
#endif

namespace dandan::abilities
{
    ActivatedAbility::ActivatedAbility(
        std::unique_ptr<costs::ICost> cost,
        std::unique_ptr<effects::IOneShotEffectDefinition> effect)
        : m_cost(std::move(cost)), m_effect(std::move(effect))
    {
    }

    std::string ActivatedAbility::display() const
    {
        std::string res{};
        if (m_cost)
        {
            res += m_cost->display();
        }
        if (m_effect)
        {
            res += m_effect->display();
        }
        return res;
    }

    // TODO: for now there are no activated abilities with options
    std::string ActivatedAbility::displayOption(
        [[maybe_unused]] size_t index) const
    {
        return display();
    }

    // TODO: for now there are no activated abilities with options
    size_t ActivatedAbility::optionsAmount() const
    {
        return 1;
    }

    std::unique_ptr<effects::IOneShotEffect> ActivatedAbility::createEffect(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] AbilityContext context) const
    {
        std::cout << "Resolving Activated ability\n";
        m_cost->pay(game, context);
        return m_effect->bind(game,
                              effects::EffectContext(context.controller_id));
    }
    [[nodiscard]] const costs::ICost *ActivatedAbility::getCost() const
    {
        return m_cost.get();
    }

    [[nodiscard]] const effects::IOneShotEffectDefinition *ActivatedAbility::
        getEffect() const
    {
        return m_effect.get();
    }
    [[nodiscard]] bool ActivatedAbility::canActivate(
        core::Game &game, const AbilityContext &context) const
    {
        if (m_cost)
        {
            auto *source_card = game.getCardByID(context.source_card_id);
            return m_cost->canPay(
                *source_card, game.getPlayer(source_card->getControllerID()));
        }
        return true;
    }

} // namespace dandan::abilities
