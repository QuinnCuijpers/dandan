#include "dandan/core/Player.h"
#include "dandan/abilities/AbilityType.h"
#include "dandan/abilities/ActivatedAbility.h"
#include "dandan/abilities/BasicLandAbility.h"
#include "dandan/abilities/ManaAbility.h"
#include "dandan/core/Game.h"
#include "dandan/mana/ManaBag.h"
#include "dandan/mana/Manapool.h"

namespace
{
    using namespace dandan;

    mana::ManaBag getMaxManaForLand(const core::Card &land,
                                    const core::Game &game)
    {
        mana::ManaBag max_mana_for_land{};
        for (const auto &ability : land.getCurrentAbilities())
        {
            if (ability.type() == abilities::AbilityType::Type::Mana)
            {
                const auto *mana_ability =
                    dynamic_cast<const abilities::ManaAbility *>(
                        &ability.definition());
                for (const auto &option :
                     mana_ability->getManaList().getOptions())
                {
                    if (option.total() > max_mana_for_land.total())
                    {
                        max_mana_for_land = option;
                    }
                }
            }
            else if (ability.type() == abilities::AbilityType::Type::BasicLand)
            {
                const auto *basic_ability =
                    dynamic_cast<const abilities::BasicLandAbility *>(
                        &ability.definition());
                const auto *mana_ability{
                    basic_ability->getManaAbility(game, ability.getContext())};
                const auto mana_list{mana_ability->getManaList()};

                for (const auto &option : mana_list.getOptions())
                {
                    if (option.total() > max_mana_for_land.total())
                    {
                        max_mana_for_land = option;
                    }
                }
            }
        }
        return max_mana_for_land;
    }

} // namespace

namespace dandan::core
{
    Player::Player(std::string name)
        : m_player_id(PlayerID::generate()), m_name(std::move(name))
    {
        std::cout << "Constructed player with name " << m_name << '\n';
    }

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
        std::cout << "Player is playing card " << card.getData().name
                  << " with ID " << card.getID().getID() << '\n';
        m_battlefield.addCard(card);
    }

    void Player::discardCard(const Card &card, Game &game)
    {
        std::cout << "Player is discarding card " << card.getData().name
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
        auto proxy_mana_pool{mana::Manapool{}};
        auto available_mana{getAvailableMana(game)};
        proxy_mana_pool.add(available_mana);

        for (const auto &card_id : m_hand.getCards())
        {
            const auto *card{game.getCardByID(card_id)};
            if (card->getData().type == Type::Instant)
            {
                const auto card_cost{card->getData().mana_cost};
                if (proxy_mana_pool.canPay(card_cost))
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

    mana::ManaBag Player::getAvailableMana(const core::Game &game) const
    {
        mana::ManaBag available_mana{};
        available_mana = available_mana.add(m_mana_pool.view());

        for (const auto &land_id : m_battlefield.getLands())
        {
            const auto *land{game.getCardByID(land_id)};
            if (land->getTapped())
            {
                continue;
            }

            const auto max_mana_for_land{getMaxManaForLand(*land, game)};
            available_mana = available_mana.add(max_mana_for_land);
        }
        std::cout << "Available mana found in canActivateSomething for player "
                     "with id "
                  << m_player_id.id() << " : " << available_mana << '\n';

        return available_mana;
    }
} // namespace dandan::core
