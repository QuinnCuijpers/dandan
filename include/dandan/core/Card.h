#ifndef DANDAN_CARD_H
#define DANDAN_CARD_H

#include "dandan/abilities/BoundAbility.h"
#include "dandan/abilities/IAbility.h"
#include "dandan/abilities/keywords/IKeyWordAbility.h"
#include "dandan/abilities/keywords/Keyword.h"
#include "dandan/core/CardData.h"
#include "dandan/core/CardID.h"
#include "dandan/core/ColorWord.h"
#include "dandan/core/Memorable.h"
#include "dandan/core/PlayerID.h"
#include "dandan/core/Stats.h"
#include "dandan/core/Target.h"
#include "dandan/core/Zone.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef DANDAN_SERIALIZE
#include <string_view>
#endif

namespace dandan::abilities
{
    class IAbility;
} // namespace dandan::abilities

namespace dandan::effects
{
    class IOneShotEffectDefinition;
    class ModalEffectDefinition;
} // namespace dandan::effects

namespace dandan::core
{
    /** @brief The mutable characteristics of a card instance.
     *
     * These values can be changed by continuous effects and are kept separate
     * from the static CardData shared by every instance of the same card.
     * @struct CardCharacteristics
     */
    struct CardCharacteristics
    {
        /// The current color of the card.
        ColorWord color{ColorWord::Colorless};
        /// The current subtypes of the card. A vector is used instead of a set
        /// because JSON serialization requires stable ordering.
        std::vector<SubType> subtypes;
        /// The current base power and toughness of the card.
        Stats base_stats;
        /// Whether the card currently loses all of its abilities.
        bool loses_all_abilities{};
        /// Abilities granted to the card in addition to its printed abilities.
        std::vector<std::unique_ptr<abilities::IAbility>> additional_abilities;

        CardCharacteristics() = default;
        ~CardCharacteristics() = default;

        /** Constructs a full set of card characteristics.
         * @param color The current color of the card.
         * @param subtypes The current subtypes of the card.
         * @param base_stats The current base power and toughness.
         * @param loses_all_abilities Whether the card loses all abilities.
         * @param additional_abilities Abilities granted to the card.
         */
        CardCharacteristics(ColorWord color, std::vector<SubType> subtypes,
                            Stats base_stats, bool loses_all_abilities,
                            std::vector<std::unique_ptr<abilities::IAbility>>
                                additional_abilities);
        /** Copies characteristics, including the additional abilities.
         * @param other The characteristics to copy.
         */
        CardCharacteristics(const CardCharacteristics &other);

        /** Copies characteristics, including the additional abilities.
         * @param other The characteristics to copy.
         * @return A reference to this object.
         */
        CardCharacteristics &operator=(const CardCharacteristics &other);

        /** Moves characteristics from another object. */
        CardCharacteristics(CardCharacteristics &&) noexcept = default;
        /** Moves characteristics from another object.
         * @return A reference to this object.
         */
        CardCharacteristics &operator=(CardCharacteristics &&) noexcept =
            default;
    };

    /** @brief A class representing a card instance in the game.
     * @class Card
     * All variable traits of the card instance are stored in this class,
     * while the static traits of the card are stored in CardData accessible
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
        [[nodiscard]] const CardID &getID() const;

        /** Get the ID of the player who controls the card.
         * @return The ID of the player who controls the card.
         */
        [[nodiscard]] PlayerID getControllerID() const;

        /** Get the tapped status of the card.
         * @return The tapped status of the card.
         */
        [[nodiscard]] bool getTapped() const;

        /** Set the tapped status of the card.
         * @param tapped The new tapped status of the card.
         */
        void setTapped(bool tapped);

        /** Get the zone the card is currently in.
         * @return The zone the card is currently in.
         */
        [[nodiscard]] Zone getZone() const;

        /** Set the zone the card is currently in.
         * @param zone The new zone the card is in.
         */
        void setZone(Zone zone);

        /** Get the static data of the card.
         * @return A const reference to the static card data.
         */
        [[nodiscard]] const CardData &getData() const;

        /** Set the ID of the player who controls the card.
         * @param new_controller_id The new controller ID.
         */
        void setControllerID(PlayerID new_controller_id);

        /** Get whether the card has summoning sickness.
         * @return True if the card has summoning sickness, false otherwise.
         */
        [[nodiscard]] bool getSummoningSickness() const;

        /** Set the state of summoning sickness.
         * @param sickness the boolean value to set the summoning sickness to
         */
        void setSummoningSickness(bool sickness);

        /** Set the attacking status of the card.
         * @param is_attacking The new attacking status of the card.
         */
        void setAttacking(bool is_attacking);

        /** Get whether the card is attacking.
         * @return True if the card is attacking, false otherwise.
         */
        [[nodiscard]] bool isAttacking() const;

        /** Get whether the card is blocked.
         * @return True if the card is blocked, false otherwise.
         */
        [[nodiscard]] bool isBlocked() const;

        /** Set the blocked status of the card.
         * @param is_blocked The new blocked status of the card.
         */
        void setBlocked(bool is_blocked);

        /** Set the blocking status of the card.
         * @param is_blocking The new blocking status of the card.
         */
        void setBlocking(bool is_blocking);

        /** Get whether the card is blocking.
         * @return True if the card is blocking, false otherwise.
         */
        [[nodiscard]] bool isBlocking() const;

        /** Get the power of the card.
         * @return The power of the card.
         */
        [[nodiscard]] int getPower() const;

        /** Get the toughness of the card.
         * @return The toughness of the card.
         */
        [[nodiscard]] int getToughness() const;

        /** Get the damage marked on the card.
         * @return The damage marked on the card.
         */
        [[nodiscard]] int getDamageMarked() const;

        /** Gets the current subtypes of the card.
         * @return A const reference to the current subtypes.
         */
        [[nodiscard]] const std::vector<SubType> &getCurrentSubTypes() const;

        /** Replaces the current subtypes of the card.
         * @param subtypes The new subtypes.
         */
        void setCurrentSubTypes(std::vector<SubType> subtypes);

        /** Gets the abilities currently granted to the card.
         * @return A reference to the current bound abilities.
         */
        std::vector<abilities::BoundAbility> &getCurrentAbilities();

        /** Gets the abilities currently granted to the card.
         * @return A const reference to the current bound abilities.
         */
        const std::vector<abilities::BoundAbility> &getCurrentAbilities() const;

        /** Gets the current card characteristics.
         * @return A reference to the current characteristics.
         */
        CardCharacteristics &getCharacteristics();

        /** Gets the characteristics from before the last update.
         * @return A reference to the previous characteristics.
         */
        CardCharacteristics &getPrevCharacteristics();

        /** Applies new characteristics to the card and records the previous
         * characteristics.
         * @param character The new characteristics.
         * @param exec_ctx The execution context.
         */
        void setCharacteristics(const CardCharacteristics &character,
                                ExecutionContext exec_ctx);

        /** Replaces the recorded previous characteristics.
         * @param character The characteristics to record as previous.
         */
        void setPrevCharacteristics(CardCharacteristics character);

        // TODO: should generate a damage event
        /** Take damage.
         * @param damage The damage to take.
         * @param exec_ctx The execution context.
         */
        void takeDamage(int damage, [[maybe_unused]] ExecutionContext exec_ctx);

        /** Checks whether the card can currently be countered.
         * @return True if the card can be countered, false otherwise.
         */
        bool canBeCountered() const;

        /** Gets the current color of the card.
         * @return The current color.
         */
        ColorWord getColor() const;

        /** Destroy the card.
         * @param exec_ctx The execution context.
         */
        void destroy(ExecutionContext exec_ctx) const;

        // TODO: verify that all per-turn card state is reset here
        /** Reset the state of the card.
         */
        void resetState();

        /** Records the chosen mode for a modal effect.
         * @param modal_effect The modal effect whose choice is recorded.
         * @param choice The chosen mode index.
         */
        void addModalChoice(const effects::ModalEffectDefinition &modal_effect,
                            int choice);

        /** Gets the recorded mode choice for a modal effect.
         * @param modal_effect The modal effect to query.
         * @return The chosen mode index.
         */
        int getModalChoice(
            const effects::ModalEffectDefinition &modal_effect) const;

        /** Records the targets chosen for an effect.
         * @param effect The effect whose targets are recorded.
         * @param targets The chosen targets.
         */
        void addTargetChoices(const effects::IOneShotEffectDefinition &effect,
                              std::vector<core::Target> targets);

        /** Gets the targets chosen for an effect.
         * @param effect The effect to query.
         * @return A const reference to the chosen targets.
         */
        const std::vector<core::Target> &getTargetChoices(
            const effects::IOneShotEffectDefinition &effect) const;

        /** Replaces instances of one color word with another.
         * @param from The color word to replace.
         * @param new_color The replacement color word.
         */
        void replaceText(ColorWord from, ColorWord new_color);
        /** Replaces instances of one basic land subtype with another.
         * @param from The subtype to replace.
         * @param new_basic The replacement subtype.
         */
        void replaceText(SubType from, SubType new_basic);

        /** Output the card to an ostream.
         * @param ostream The ostream to output the card to.
         * @param card The card to output.
         * @return The ostream.
         */
        friend std::ostream &operator<<(std::ostream &ostream,
                                        const Card &card);

        // TODO: should only be public to Game::GameSetup
        /** Replaces the abilities currently granted to the card.
         * @param abilities The new bound abilities.
         */
        void setBoundAbilities(std::vector<abilities::BoundAbility> abilities);

        /** Stores a value in the card's memory link map.
         * @param key The key identifying the value.
         * @param value The value to remember.
         */
        void remember(const std::string &key, Memorable value);

        /** Gets the card's memory link map.
         * @return A reference to the link map.
         */
        std::unordered_map<std::string, Memorable> &linkMap();

        /** Gets the card's memory link map.
         * @return A const reference to the link map.
         */
        const std::unordered_map<std::string, Memorable> &linkMap() const;

        /** Checks whether the card has the given keyword ability.
         * @param key_word The keyword to look for.
         * @return True if the card has the keyword, false otherwise.
         */
        bool hasKeyword(abilities::Keyword key_word) const;

        /** Finds the first current ability of the requested type.
         * @tparam T The ability type to find.
         * @return A pointer to the ability, or nullptr if it is not present.
         */
        template <typename T> const T *getAbility() const
        {
            auto ability_iter = std::find_if(
                m_current_abilities.begin(), m_current_abilities.end(),
                [](const auto &ability)
                {
                    return dynamic_cast<const T *>(&ability.definition()) !=
                           nullptr;
                });

            if (ability_iter == m_current_abilities.end())
            {
                return nullptr;
            }

            return dynamic_cast<const T *>(&ability_iter->definition());
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
        const CardData *m_card_data;

        void setCurrentPower(int power);

        void setCurrentToughness(int toughness);
    };
} // namespace dandan::core

#endif
