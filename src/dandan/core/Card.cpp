#include "dandan/core/Card.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/core/CardData.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/Game.h"
#include "dandan/utils/log.h"
#include <vector>

#ifdef DANDAN_SERIALIZE
#include "dandan/core/CardDataFactory.h"
#endif

namespace dandan::core
{
#ifdef DANDAN_SERIALIZE
    Card::Card(std::string_view card_name, PlayerID controller_id)
        : m_card_id(CardID::generate()), m_controller_id(controller_id),
          m_card_data(&CardDataFactory::createCardData(card_name))
    {
        DLOGI << "Creating card: " << card_name
              << " with ID: " << m_card_id.getID() << '\n';
        if (m_card_data != nullptr)
        {
            auto stats = m_card_data->stats;
            if (stats.has_value())
            {
                setCurrentPower(stats->power);
                setCurrentToughness(stats->toughness);
            }
            setCurrentSubTypes(m_card_data->subtypes);
            getCharacteristics().color = m_card_data->color;

            auto bound_abilities{std::vector<abilities::BoundAbility>{}};
            for (const auto &ability : m_card_data->abilities)
            {
                auto *definition{ability.get()};
                auto bound{abilities::BoundAbility{*definition, this}};
                bound_abilities.push_back(bound);
            }
            m_current_abilities = std::move(bound_abilities);
        }
    }
#endif

    Card::Card(CardData *card_data, PlayerID controller_id)
        : m_card_id(CardID::generate()), m_controller_id(controller_id),
          m_card_data(card_data)
    {
        DLOGI << "Creating card: " << card_data->name
              << " with ID: " << m_card_id.getID() << '\n';
        if (m_card_data != nullptr)
        {
            auto stats = m_card_data->stats;
            if (stats.has_value())
            {
                setCurrentPower(stats->power);
                setCurrentToughness(stats->toughness);
            }
            setCurrentSubTypes(m_card_data->subtypes);
            getCharacteristics().color = m_card_data->color;
        }
    }

    void Card::destroy([[maybe_unused]] ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};

        std::cout << "Destroying card " << getData().name << '\n';
        auto *card{card_registry[getID()]};
        auto &player{game.getPlayer(card->getControllerID())};
        game.moveCardFromZone(player, *card);
        // remove from managers
        game.eventManager().unsubscribe(*card);
        game.conditionManager().removeCardConditions(card->getID());
        game.preventionManager().unsubscribe(card->getID());
        game.replacementManager().unsubscribe(*card);
        game.graveyard().addCard(*card);
    }

    [[nodiscard]] const CardID &Card::getID() const
    {
        return m_card_id;
    }

    /** Get the ID of the player who controls the card.
     * @return The ID of the player who controls the card.
     */
    [[nodiscard]] PlayerID Card::getControllerID() const
    {
        return m_controller_id;
    }

    /** Get the tapped status of the card.
     * @return The tapped status of the card.
     */
    [[nodiscard]] bool Card::getTapped() const
    {
        return m_tapped;
    }

    /** Set the tapped status of the card.
     * @param tapped The new tapped status of the card.
     */
    void Card::setTapped(bool tapped)
    {
        m_tapped = tapped;
    }

    /** Get the zone the card is currently in.
     * @return The zone the card is currently in.
     */
    [[nodiscard]] Zone Card::getZone() const
    {
        return m_zone;
    }

    /** Set the zone the card is currently in.
     * @param zone The new zone the card is in.
     */
    void Card::setZone(Zone zone)
    {
        m_zone = zone;
    }

    /** Get the static data of the card.
     * @return A const reference to the static card data.
     */
    [[nodiscard]] const CardData &Card::getData() const
    {
        return *m_card_data;
    }

    /** Set the ID of the player who controls the card.
     * @param new_controller_id The new controller ID.
     */
    void Card::setControllerID(PlayerID new_controller_id)
    {
        m_controller_id = new_controller_id;
    }

    /** Get whether the card has summoning sickness.
     * @return True if the card has summoning sickness, false otherwise.
     */
    [[nodiscard]] bool Card::getSummoningSickness() const
    {
        return m_summoning_sick;
    }

    /** Set the state of summoning sickness.
     * @param sickness the boolean value to set the summoning sickness to
     */
    void Card::setSummoningSickness(bool sickness)

    {
        m_summoning_sick = sickness;
    }

    /** Set the attacking status of the card.
     * @param is_attacking The new attacking status of the card.
     */
    void Card::setAttacking(bool is_attacking)
    {
        m_is_attacking = is_attacking;
    }

    /** Get whether the card is attacking.
     * @return True if the card is attacking, false otherwise.
     */
    [[nodiscard]] bool Card::isAttacking() const
    {
        return m_is_attacking;
    }

    /** Get whether the card is blocked.
     * @return True if the card is blocked, false otherwise.
     */
    [[nodiscard]] bool Card::isBlocked() const
    {
        return m_is_blocked;
    }

    /** Set the blocked status of the card.
     * @param is_blocked The new blocked status of the card.
     */
    void Card::setBlocked(bool is_blocked)
    {
        m_is_blocked = is_blocked;
    }

    /** Set the blocking status of the card.
     * @param is_blocking The new blocking status of the card.
     */
    void Card::setBlocking(bool is_blocking)
    {
        m_blocking = is_blocking;
    }

    /** Get whether the card is blocking.
     * @return True if the card is blocking, false otherwise.
     */
    [[nodiscard]] bool Card::isBlocking() const
    {
        return m_blocking;
    }

    /** Get the power of the card.
     * @return The power of the card.
     */
    [[nodiscard]] int Card::getPower() const
    {
        return m_characteristics.base_stats.power;
    }

    /** Get the toughness of the card.
     * @return The toughness of the card.
     */
    [[nodiscard]] int Card::getToughness() const
    {
        return m_characteristics.base_stats.toughness;
    }

    /** Get the damage marked on the card.
     * @return The damage marked on the card.
     */
    [[nodiscard]] int Card::getDamageMarked() const
    {
        return m_marked_damage;
    }

    [[nodiscard]] const std::vector<SubType> &Card::getCurrentSubTypes() const
    {
        return m_characteristics.subtypes;
    }

    void Card::setCurrentSubTypes(std::vector<SubType> subtypes)
    {
        m_characteristics.subtypes = std::move(subtypes);
    }

    std::vector<abilities::BoundAbility> &Card::getCurrentAbilities()
    {
        return m_current_abilities;
    }

    const std::vector<abilities::BoundAbility> &Card::getCurrentAbilities()
        const
    {
        return m_current_abilities;
    }

    CardCharacteristics &Card::getCharacteristics()
    {
        return m_characteristics;
    }

    CardCharacteristics &Card::getPrevCharacteristics()
    {
        return m_prev_characteristics;
    }

    void setCharacteristics(const CardCharacteristics &character,
                            ExecutionContext exec_ctx);

    void Card::setPrevCharacteristics(CardCharacteristics character)
    {
        m_prev_characteristics = std::move(character);
    }

    // TODO: should generate a damage event
    /** Take damage.
     * @param damage The damage to take.
     * @param game The game instance.
     */
    void Card::takeDamage(int damage,
                          [[maybe_unused]] ExecutionContext exec_ctx)
    {
        m_marked_damage += damage;
    }

    bool Card::canBeCountered() const
    {
        return m_can_be_countered;
    }

    ColorWord Card::getColor() const
    {
        return m_characteristics.color;
    }

    // TODO: check this thoroughly
    /** Reset the state of the card.
     */
    void Card::resetState()
    {
        m_summoning_sick = true;
        m_is_attacking = false;
        m_is_blocked = false;
        m_blocking = false;
        if (const auto stats = getData().stats; stats.has_value())
        {
            setCurrentPower(stats->power);
            setCurrentToughness(stats->toughness);
        }
        m_marked_damage = 0;
    }

    void Card::addModalChoice(
        const effects::ModalEffectDefinition &modal_effect, int choice)
    {
        m_modal_choices[&modal_effect] = choice;
    }

    int Card::getModalChoice(
        const effects::ModalEffectDefinition &modal_effect) const
    {
        auto iter = m_modal_choices.find(&modal_effect);
        if (iter == m_modal_choices.end())
        {
            throw std::runtime_error(
                "No modal choice found for the given modal effect");
        }
        return iter->second;
    }

    void Card::addTargetChoices(const effects::IOneShotEffectDefinition &effect,
                                std::vector<core::Target> targets)
    {
        m_target_choices[&effect] = std::move(targets);
    }

    const std::vector<core::Target> &Card::getTargetChoices(
        const effects::IOneShotEffectDefinition &effect) const
    {
        auto iter = m_target_choices.find(&effect);
        if (iter == m_target_choices.end())
        {
            throw std::runtime_error(
                "No target choices found for the given target requirement");
        }
        return iter->second;
    }

    void replaceText(ColorWord from, ColorWord new_color);
    void replaceText(SubType from, SubType new_basic);

    std::ostream &operator<<(std::ostream &ostream, const Card &card)
    {
        if (card.m_card_data == nullptr)
        {
            ostream << "Card{ID: " << card.m_card_id.getID()
                    << ", controller ID: " << card.m_controller_id.id()
                    << ", tapped: " << card.m_tapped << ", data: nullptr}"
                    << ", summoning sick: " << card.m_summoning_sick << '}';
            return ostream;
        }
        ostream << "Card{ID: " << card.m_card_id.getID()
                << ", controller ID: " << card.m_controller_id.id()
                << ", tapped: " << card.m_tapped
                << ", summoning sick: " << card.m_summoning_sick
                << ", data: " << card.m_card_data << '}';
        return ostream;
    }

    // TODO: should only be public to Game::GameSetup
    void Card::setBoundAbilities(std::vector<abilities::BoundAbility> abilities)
    {
        m_current_abilities = std::move(abilities);
    }

    void Card::remember(const std::string &key, Memorable value)
    {
        m_link_map[key] = std::move(value);
    }

    std::unordered_map<std::string, Memorable> &Card::linkMap()
    {
        return m_link_map;
    }

    const std::unordered_map<std::string, Memorable> &Card::linkMap() const
    {
        return m_link_map;
    }

    void Card::setCharacteristics(const CardCharacteristics &character,
                                  ExecutionContext exec_ctx)
    {
        auto &game{exec_ctx.state.get()};

        std::cout << "Setting characteristics of cardID: " << m_card_id << '\n';
        m_characteristics = character;
        if (character.loses_all_abilities)
        {
            for (const auto &ability : m_current_abilities)
            {

                game.eventManager().unsubscribe(ability);

                game.replacementManager().unsubscribe(ability);

                game.preventionManager().unsubscribe(ability);

                game.conditionManager().removeStateTriggeredAbility(ability);
            }
            m_current_abilities.clear();
        }
        std::cout << "Size of additional abilities: "
                  << character.additional_abilities.size() << '\n';
        for (const auto *ability : character.additional_abilities)
        {
            std::cout << "Adding ability: \n";
            auto bound{abilities::BoundAbility{*ability, this}};
            m_current_abilities.push_back(bound);
        }
    }

    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    void Card::replaceText(ColorWord from, ColorWord new_color)
    {
        // change controls island conditions
        for (auto &ability : getCurrentAbilities())
        {
            ability.addTextReplacement({from, new_color});
        }
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)

    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    void Card::replaceText(SubType from, SubType new_basic)
    {
        for (auto type : getCurrentSubTypes())
        {
            if (type == from)
            {
                setCurrentSubTypes({new_basic});
            }
        }

        for (auto &ability : getCurrentAbilities())
        {
            ability.addTextReplacement({from, new_basic});
        }
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)
} // namespace dandan::core
