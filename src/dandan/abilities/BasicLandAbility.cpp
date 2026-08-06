#include "dandan/abilities/BasicLandAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/mana/ManaList.h"
#include "dandan/mana/ManaPip.h"
#include <memory>
#include <unordered_map>

namespace
{
    std::unordered_map<dandan::core::SubType,
                       std::unique_ptr<dandan::abilities::ManaAbility>>
    make_map()
    {

        std::unordered_map<dandan::core::SubType,
                           std::unique_ptr<dandan::abilities::ManaAbility>>
            map{};

        map.emplace(dandan::core::SubType::Plains,
                    std::make_unique<dandan::abilities::ManaAbility>(
                        dandan::mana::ManaList{
                            std::make_unique<dandan::mana::WhiteMana>(1)}));
        map.emplace(dandan::core::SubType::Island,
                    std::make_unique<dandan::abilities::ManaAbility>(
                        dandan::mana::ManaList{
                            std::make_unique<dandan::mana::BlueMana>(1)}));
        map.emplace(dandan::core::SubType::Swamp,
                    std::make_unique<dandan::abilities::ManaAbility>(
                        dandan::mana::ManaList{
                            std::make_unique<dandan::mana::BlackMana>(1)}));
        map.emplace(dandan::core::SubType::Mountain,
                    std::make_unique<dandan::abilities::ManaAbility>(
                        dandan::mana::ManaList{
                            std::make_unique<dandan::mana::RedMana>(1)}));
        map.emplace(dandan::core::SubType::Forest,
                    std::make_unique<dandan::abilities::ManaAbility>(
                        dandan::mana::ManaList{
                            std::make_unique<dandan::mana::GreenMana>(1)}));

        return map;
    }
} // namespace

namespace dandan::abilities
{

    BasicLandAbility::BasicLandAbility() : m_basic_land_ability_map{make_map()}
    {
    }

    [[nodiscard]] std::string BasicLandAbility::display() const
    {
        // for now display islands
        return m_basic_land_ability_map.at(core::SubType::Island)->display();
    }

    [[nodiscard]] std::string BasicLandAbility::displayOption(
        [[maybe_unused]] size_t index) const
    {
        // FIXME: hacky when cards can have multiple subtypes
        return display();
    }

    [[nodiscard]] bool BasicLandAbility::canActivate(
        [[maybe_unused]] core::Game &game,
        [[maybe_unused]] const AbilityContext &context) const
    {
        auto res{false};
        auto *card{game.getCardByID(context.source_card_id)};
        for (auto subtype : card->getCurrentSubTypes())
        {
            switch (subtype)
            {

            case core::SubType::Forest:
            case core::SubType::Island:
            case core::SubType::Mountain:
            case core::SubType::Plains:
            case core::SubType::Swamp:
                res = res || m_basic_land_ability_map.at(subtype)->canActivate(
                                 game, context);
            case core::SubType::None:
            case core::SubType::Fish:
            case core::SubType::Illusion:
            case core::SubType::Dragon:
                break;
            }
        }
        return res;
    }

    [[nodiscard]] size_t BasicLandAbility::optionsAmount() const
    {
        // FIXME:
        // hacky when cards can have multiple subtypes
        return 1;
    }

    std::unique_ptr<effects::IOneShotEffect> BasicLandAbility::createEffect(
        core::Game &game, AbilityContext context) const
    {
        const auto *cardp = game.getCardByID(context.source_card_id);
        assert(cardp->getCurrentSubTypes().size() == 1);
        auto type{cardp->getCurrentSubTypes()[0]};
        return m_basic_land_ability_map.at(type)->createEffect(game, context);
    }

    const ManaAbility *BasicLandAbility::getManaAbility(
        const core::Game &game, const AbilityContext &context) const
    {
        const auto *card{game.getCardByID(context.source_card_id)};
        assert(card->getCurrentSubTypes().size() == 1);
        auto type{card->getCurrentSubTypes()[0]};
        return m_basic_land_ability_map.at(type).get();
    }
}; // namespace dandan::abilities
