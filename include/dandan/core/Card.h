#ifndef DANDAN_CARD_H
#define DANDAN_CARD_H

#include "CardData.h"
#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/core/CardCharacteristics.h"
#include "dandan/core/CardID.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/Memorable.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/Target.h"
#include "dandan/core/Zone.h"
#include "dandan/effects/one_shot/IOneShotEffectDefinition.h"
#include "dandan/effects/one_shot/ModalEffect.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifdef DANDAN_SERIALIZE
#include <string_view>
#endif

namespace dandan::core
{

    /** @brief A class representing a card instance in the game.
     * @class Card
     * All variable traits of the card instance are stored in this class,
     * while the static traits of the card are stored in CardData accesible
     * through `getData()`.
     */
    class Card
    {
    public:
#ifdef DANDAN_SERIALIZE
        explicit Card(std::string_view card_name,
                      PlayerID controller_id = PlayerID::getInvalidID());

#endif

        /** Constructor for creating a card instance.
         * @param card_data A pointer to the static card data.
         * @param controller_id The ID of the player who controls the card.
         */
        explicit Card(CardData *card_data,
                      PlayerID controller_id = PlayerID::getInvalidID());

        /** Get the ID of the card.
         * @return The ID of the card.
         */
        [[nodiscard]] const CardID &getID() const
        {
            return m_card_id;
        }
        /** Get the ID of the player who controls the card.
         * @return The ID of the player who controls the card.
         */
        [[nodiscard]] PlayerID getControllerID() const
        {
            return m_controller_id;
        }

        /** Get the tapped status of the card.
         * @return The tapped status of the card.
         */
        [[nodiscard]] bool getTapped() const
        {
            return m_tapped;
        }

        /** Set the tapped status of the card.
         * @param tapped The new tapped status of the card.
         */
        void setTapped(bool tapped)
        {
            m_tapped = tapped;
        }

        /** Get the zone the card is currently in.
         * @return The zone the card is currently in.
         */
        [[nodiscard]] Zone getZone() const
        {
            return m_zone;
        }

        /** Set the zone the card is currently in.
         * @param zone The new zone the card is in.
         */
        void setZone(Zone zone)
        {
            std::cout << "Setting zone of card " << getData().getName()
                      << " with ID: " << getID().getID() << " to "
                      << zoneToString(zone) << '\n';
            m_zone = zone;
        }

        /** Get the static data of the card.
         * @return A const reference to the static card data.
         */
        [[nodiscard]] const CardData &getData() const
        {
            return *m_card_data;
        }

        /** Set the ID of the player who controls the card.
         * @param new_controller_id The new controller ID.
         */
        void setControllerID(PlayerID new_controller_id)
        {
            m_controller_id = new_controller_id;
        }

        /** Get whether the card has summoning sickness.
         * @return True if the card has summoning sickness, false otherwise.
         */
        [[nodiscard]] bool getSummoningSickness() const
        {
            return m_summoning_sick;
        }

        /** Set the state of summoning sickness.
         * @param sickness the boolean value to set the summoning sickness to
         */
        void setSummoningSickness(bool sickness)

        {
            m_summoning_sick = sickness;
        }

        /** Set the attacking status of the card.
         * @param is_attacking The new attacking status of the card.
         */
        void setAttacking(bool is_attacking)
        {
            m_is_attacking = is_attacking;
        }

        /** Get whether the card is attacking.
         * @return True if the card is attacking, false otherwise.
         */
        [[nodiscard]] bool isAttacking() const
        {
            return m_is_attacking;
        }

        /** Get whether the card is blocked.
         * @return True if the card is blocked, false otherwise.
         */
        [[nodiscard]] bool isBlocked() const
        {
            return m_is_blocked;
        }

        /** Set the blocked status of the card.
         * @param is_blocked The new blocked status of the card.
         */
        void setBlocked(bool is_blocked)
        {
            m_is_blocked = is_blocked;
        }

        /** Set the blocking status of the card.
         * @param is_blocking The new blocking status of the card.
         */
        void setBlocking(bool is_blocking)
        {
            m_blocking = is_blocking;
        }

        /** Get whether the card is blocking.
         * @return True if the card is blocking, false otherwise.
         */
        [[nodiscard]] bool isBlocking() const
        {
            return m_blocking;
        }

        /** Get the power of the card.
         * @return The power of the card.
         */
        [[nodiscard]] int getPower() const
        {
            return m_characteristics.base_stats.power;
        }

        /** Get the toughness of the card.
         * @return The toughness of the card.
         */
        [[nodiscard]] int getToughness() const
        {
            return m_characteristics.base_stats.toughness;
        }

        /** Get the damage marked on the card.
         * @return The damage marked on the card.
         */
        [[nodiscard]] int getDamageMarked() const
        {
            return m_marked_damage;
        }

        [[nodiscard]] const std::vector<SubType> &getCurrentSubTypes() const
        {
            return m_characteristics.subtypes;
        }

        void setCurrentSubTypes(std::vector<SubType> subtypes)
        {
            m_characteristics.subtypes = std::move(subtypes);
        }

        std::vector<abilities::BoundAbility> &getCurrentAbilities()
        {
            return m_current_abilities;
        }

        const std::vector<abilities::BoundAbility> &getCurrentAbilities() const
        {
            return m_current_abilities;
        }

        CardCharacteristics &getCharacteristics()
        {
            return m_characteristics;
        }

        CardCharacteristics &getPrevCharacteristics()
        {
            return m_prev_characteristics;
        }

        void setCharacteristics(const CardCharacteristics &character,
                                Game &game);

        void setPrevCharacteristics(CardCharacteristics character)
        {
            m_prev_characteristics = std::move(character);
        }

        // TODO: should generate a damage event
        /** Take damage.
         * @param damage The damage to take.
         * @param game The game instance.
         */
        void takeDamage(int damage, [[maybe_unused]] Game &game)
        {
            m_marked_damage += damage;
        }

        bool canBeCountered() const
        {
            return m_can_be_countered;
        }

        /** Destroy the card.
         * @param game The game instance.
         */
        void destroy(Game &game) const;

        // TODO: check this thoroughly
        /** Reset the state of the card.
         */
        void resetState()
        {
            m_summoning_sick = true;
            m_is_attacking = false;
            m_is_blocked = false;
            m_blocking = false;
            if (const auto stats = getData().getStats(); stats.has_value())
            {
                setCurrentPower(stats->power);
                setCurrentToughness(stats->toughness);
            }
            m_marked_damage = 0;
        }

        void addModalChoice(const effects::ModalEffectDefinition &modal_effect,
                            int choice)
        {
            m_modal_choices[&modal_effect] = choice;
        }

        int getModalChoice(
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

        void addTargetChoices(const effects::IOneShotEffectDefinition &effect,
                              std::vector<core::Target> targets)
        {
            m_target_choices[&effect] = std::move(targets);
        }

        const std::vector<core::Target> &getTargetChoices(
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

        /** Output the card to an ostream.
         * @param ostream The ostream to output the card to.
         * @param card The card to output.
         * @return The ostream.
         */
        friend std::ostream &operator<<(std::ostream &ostream, const Card &card)
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
                    << ", data: " << *card.m_card_data << '}';
            return ostream;
        }

        // TODO: should only be public to Game::GameSetup
        void setBoundAbilities(std::vector<abilities::BoundAbility> abilities)
        {
            m_current_abilities = std::move(abilities);
        }

        void remember(const std::string &key, Memorable value)
        {
            m_link_map[key] = std::move(value);
        }

        std::unordered_map<std::string, Memorable> &linkMap()
        {
            return m_link_map;
        }

        const std::unordered_map<std::string, Memorable> &linkMap() const
        {
            return m_link_map;
        }

    private:
        CardID m_card_id;
        PlayerID m_controller_id;

        std::unordered_map<const effects::ModalEffectDefinition *, int>
            m_modal_choices;
        std::unordered_map<const effects::IOneShotEffectDefinition *,
                           std::vector<core::Target>>
            m_target_choices;

        bool m_tapped{false};
        Zone m_zone{Zone::LIBRARY};

        bool m_summoning_sick{true};
        bool m_is_attacking{false};
        bool m_is_blocked{false};
        bool m_blocking{false};

        bool m_can_be_countered{true};

        std::vector<abilities::BoundAbility> m_current_abilities;

        CardCharacteristics m_characteristics;
        CardCharacteristics m_prev_characteristics;

        int m_marked_damage{};

        // the memory link map of the card, which allows effects to store memory
        // used for other effects
        std::unordered_map<std::string, Memorable> m_link_map;

        // static pointer to card data, as the data is shared among all
        // instances of the same card, and we want to avoid copying it for each
        // instance
        CardData *m_card_data;

        void setCurrentPower(int power)
        {
            m_characteristics.base_stats.power = power;
        }

        void setCurrentToughness(int toughness)
        {
            m_characteristics.base_stats.toughness = toughness;
        }
    };
} // namespace dandan::core

#endif
