#ifndef DANDAN_BASICLANDABILITY_H
#define DANDAN_BASICLANDABILITY_H

#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/mana/BlackMana.h"
#include "dandan/mana/BlueMana.h"
#include "dandan/mana/GreenMana.h"
#include "dandan/mana/RedMana.h"
#include "dandan/mana/WhiteMana.h"
#include <unordered_map>

namespace dandan::abilities
{
    static const std::unordered_map<core::CardData::SubType,
                                    const ManaAbility *>
        s_land_ability_map{
            {core::CardData::SubType::Plains,
             new ManaAbility(
                 mana::ManaList{std::make_unique<mana::WhiteMana>(1)})},
            {core::CardData::SubType::Island,
             new ManaAbility(
                 mana::ManaList{std::make_unique<mana::BlueMana>(1)})},
            {core::CardData::SubType::Swamp,
             new ManaAbility(
                 mana::ManaList{std::make_unique<mana::BlackMana>(1)})},
            {core::CardData::SubType::Mountain,
             new ManaAbility(
                 mana::ManaList{std::make_unique<mana::RedMana>(1)})},
            {core::CardData::SubType::Forest,
             new ManaAbility(
                 mana::ManaList{std::make_unique<mana::GreenMana>(1)})},
        };

    /** @brief An ability that represents a basic land's ability to produce
     * mana.
     * @class BasicLandAbility
     *
     * @implements IAbility
     */
    class BasicLandAbility final : public IAbility
    {
    public:
        BasicLandAbility() = default;

        [[nodiscard]] std::string display() const override
        {
            // for now display islands
            return m_basic_land_ability_map->at(core::CardData::SubType::Island)
                ->display();
        }

        [[nodiscard]] std::string displayOption(
            [[maybe_unused]] size_t index) const override
        {
            // FIXME: hacky when cards can have multiple subtypes
            return display();
        }

        [[nodiscard]] bool canActivate(
            [[maybe_unused]] core::Game &game,
            [[maybe_unused]] AbilityContext context) const override
        {
            auto *card{game.getCardByID(context.source_card_id)};
            return m_basic_land_ability_map->at(card->getCurrentSubType())
                ->canActivate(game, context);
        }

        /** @brief Get the number of options for the ability
         * @return The number of options
         */
        [[nodiscard]] size_t optionsAmount() const override
        {
            // FIXME:
            // hacky when cards can have multiple subtypes
            return 1;
        }

        std::unique_ptr<effects::IOneShotEffect> createEffect(
            core::Game &game, AbilityContext context) const override
        {
            auto *cardp = game.getCardByID(context.source_card_id);
            return m_basic_land_ability_map->at(cardp->getCurrentSubType())
                ->createEffect(game, context);
        }

    private:
        const std::unordered_map<core::CardData::SubType, const ManaAbility *>
            *m_basic_land_ability_map = &s_land_ability_map;
    };
} // namespace dandan::abilities

#endif