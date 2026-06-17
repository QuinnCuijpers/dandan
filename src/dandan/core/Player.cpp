#include "dandan/core/Player.h"
#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/BasicLandAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/core/CardData.h"
#include "dandan/core/Game.h"
#include "dandan/effects/one_shot/AddManaEffect.h"
#include "dandan/mana/Mana.h"

namespace dandan::core
{
    void Player::drawCard(Game &game)
    {
        auto &library{game.library()};
        if (library.getCards().empty())
        {
            std::cout << "library is empty, cannot draw card\n";
            setDrewCardFromEmptyLibrary(true);
            return;
        }
        auto card_id = library.draw();
        auto *card{game.getCardByID(card_id)};
        card->setControllerID(m_player_id);
        m_hand.addCard(*card);
    }

    void Player::playCard(Card &card)
    {
        std::cout << "Player is playing card " << card.getData().getName()
                  << " with ID " << card.getID().getID() << '\n';
        m_battlefield.addCard(card);
    }

    void Player::discardCard(const Card &card, Game &game)
    {
        std::cout << "Player is discarding card " << card.getData().getName()
                  << '\n';
        m_hand.discardCard(card.getID(), game);
    }

    void Player::sacrificeCard(Card &card, Game &game)
    {
        std::cout << "Player is sacrificing card with ID "
                  << card.getID().getID() << '\n';
        m_battlefield.sacrificeCard(card, game);
    }

    bool Player::canActivateSomething(Game &game) const
    {
        mana::Mana available_mana{};
        for (const auto &[type, amount] : m_mana_pool.getMana())
        {
            available_mana.addMana(type, amount);
        }

        for (const auto &land_id : m_battlefield.getLands())
        {
            auto *land{game.getCardByID(land_id)};
            if (land->getTapped())
            {
                continue;
            }

            mana::ManaMap max_mana_for_land{};
            for (const auto &ability : land->getCurrentAbilities())
            {
                if (ability.type() == abilities::AbilityType::Type::Mana)
                {
                    const auto *mana_ability =
                        dynamic_cast<const abilities::ManaAbility *>(
                            &ability.definition());
                    for (const auto &option :
                         mana_ability->getManaList()->getOptions())
                    {
                        if (mana::MoreManaThan(option->getMana(),
                                               max_mana_for_land))
                        {
                            max_mana_for_land = option->getMana();
                        }
                    }
                }
                else if (ability.type() ==
                         abilities::AbilityType::Type::BasicLand)
                {
                    const auto *basic_ability =
                        dynamic_cast<const abilities::BasicLandAbility *>(
                            &ability.definition());
                    const auto *mana_ability{basic_ability->getManaAbility(
                        game, ability.getContext())};
                    const auto *mana_list{mana_ability->getManaList()};

                    for (const auto &option : mana_list->getOptions())
                    {
                        if (mana::MoreManaThan(option->getMana(),
                                               max_mana_for_land))
                        {
                            max_mana_for_land = option->getMana();
                        }
                    }
                }
            }

            for (const auto &[type, amount] : max_mana_for_land)
            {
                available_mana.addMana(type, amount);
            }
        }
        std::cout << "Available mana found in canActivateSomething for player "
                     "with id "
                  << m_player_id.id() << " : " << available_mana << '\n';
        for (const auto &card_id : m_hand.getCards())
        {
            auto *card{game.getCardByID(card_id)};
            if (card->getData().getType() == CardData::Type::Instant)
            {
                const auto *card_cost{card->getData().getCost()};
                if (available_mana.canPay(*card_cost))
                {
                    return true;
                }
            }
            for (const auto &ability : card->getCurrentAbilities())
            {
                if (ability.type() == abilities::AbilityType::Type::Activated)
                {
                    const auto *activated_ability =
                        dynamic_cast<const abilities::ActivatedAbility *>(
                            &ability.definition());
                    if (activated_ability->canActivate(game,
                                                       ability.getContext()))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
} // namespace dandan::core