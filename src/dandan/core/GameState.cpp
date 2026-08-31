#include "dandan/core/GameState.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/core/actions/ActivateAbilityAction.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/core/engine/EventManager.h"
#include "dandan/core/engine/PreventionManager.h"
#include "dandan/core/engine/ReplacementManager.h"
#include "dandan/utils/overloadVisitor.h"
#include <stdexcept>

namespace
{
    using namespace dandan;

    std::vector<core::Target> getCreaturesForPlayer(const core::Player &player)
    {
        auto targets{std::vector<core::Target>{}};

        const auto &creatures =
            player.battlefield().permanents().at(core::Type::Creature);

        std::transform(
            creatures.begin(), creatures.end(), std::back_inserter(targets),
            [](const core::Permanent &perm) -> core::Target { return perm; });

        return targets;
    }

} // namespace

namespace dandan::core
{
    void GameState::handleActivate(const std::string &input,
                                   ExecutionContext exec_ctx)
    {
        auto &card_registry{exec_ctx.cards.get()};
        auto &prevention_manager{exec_ctx.prevention_manager.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};
        auto &event_manager{exec_ctx.event_manager.get()};
        auto &replacement_manager{exec_ctx.replacement_manager.get()};

        int card_id = std::stoi(input.substr(std::size("activate ") - 1));

        const auto *cardp{card_registry[card_id]};

        if (cardp->getZone() != Zone::BATTLEFIELD &&
            cardp->getZone() != Zone::HAND)
        {
            std::cout << "Card is not on the battlefield or in hand\n";
            return;
        }

        size_t ability_index{};
        int display_index{};

        const auto &abilities = cardp->getCurrentAbilities();

        auto ability_indices{
            std::vector<std::pair<size_t, std::optional<size_t>>>{}};

        auto base_ability_context{abilities::AbilityContext{
            cardp->getID(), cardp->getControllerID()}};

        for (const auto &ability : cardp->getCurrentAbilities())
        {
            const auto &underlying_ability{ability.definition()};
            if (!underlying_ability.canActivate(exec_ctx, base_ability_context))
            {
                ++ability_index;
                continue;
            }
            if (underlying_ability.optionsAmount() > 1)
            {
                size_t modal_index{};
                for (size_t option_index{};
                     option_index < underlying_ability.optionsAmount();
                     ++option_index)
                {
                    std::cout << "Ability " << display_index++ << ": ";
                    std::cout << underlying_ability.displayOption(option_index);
                    std::cout << ".\n";
                    ability_indices.emplace_back(ability_index, modal_index);
                    ++modal_index;
                }
            }
            else
            {
                std::cout << "Ability " << display_index++ << ": "
                          << underlying_ability.display();
                std::cout << ".\n";
                ability_indices.emplace_back(ability_index, std::nullopt);
            }
            ++ability_index;
        }

        if (ability_indices.empty())
        {
            std::cout << "No activatable abilities\n";
            return;
        }

        size_t real_index{};
        std::optional<size_t> modal_index_opt{};

        if (ability_indices.size() == 1)
        {
            std::cout << "Only one activatable ability, activating it\n";
            real_index = ability_indices[0].first;
            modal_index_opt = ability_indices[0].second;
        }
        else
        {
            std::cout << "Which ability do you want to activate? "
                         "(enter the index of the "
                         "ability)\n";

            std::string ability_input;
            std::getline(istream, ability_input);
            size_t ability_index_input = std::stoull(ability_input);
            if (ability_index_input >= ability_indices.size())
            {
                std::cout << "Invalid ability index\n";
                return;
            }
            real_index = ability_indices[ability_index_input].first;
            modal_index_opt = ability_indices[ability_index_input].second;
        }

        const auto ability = abilities[real_index];

        auto ability_context{abilities::AbilityContext{
            cardp->getID(), cardp->getControllerID(), modal_index_opt}};

        auto action = std::make_unique<ActivateAbilityAction>(
            &ability.definition(), ability_context);

        if (prevention_manager.isPrevented(*action, exec_ctx))
        {
            std::cout << "Action prevented\n";
            return;
        }

        auto effect{action->createEffect(exec_ctx)};
        if (!effect)
        {
            std::cout << "No effect created for ability activation\n";
            return;
        }
        std::cout << "Created effect for ability activation\n";
        const auto &final_effect{
            replacement_manager.applyReplacementEffects(*effect, exec_ctx)};

        auto event{final_effect->apply(exec_ctx)};
        if (event)
        {
            event_manager.notify(*event, exec_ctx);
        }
    }

    void GameState::handlePlay(const std::string &input,
                               ExecutionContext exec_ctx)
    {
        auto &prevention_manager{exec_ctx.prevention_manager.get()};
        auto &event_manager{exec_ctx.event_manager.get()};
        auto &replacement_manager{exec_ctx.replacement_manager.get()};

        int card_id = std::stoi(input.substr(std::size("play ") - 1));

        auto action =
            std::make_unique<PlayCardAction>(CardID::fromInt(card_id));

        if (prevention_manager.isPrevented(*action, exec_ctx))
        {
            std::cout << "Action prevented\n";
            return;
        }

        auto effect{action->createEffect(exec_ctx)};
        const auto &final_effect{
            replacement_manager.applyReplacementEffects(*effect, exec_ctx)};

        auto event{final_effect->apply(exec_ctx)};
        if (event)
        {
            event_manager.notify(*event, exec_ctx);
        }
    }
    void GameState::quit(const Player &player) const
    {
        // Implementation for quitting the game
        // for now we only support 2 players so we can just end the game

        auto winner_id{getNextPlayerID(player.getID())};
        const auto &winner{getPlayer(winner_id)};

        std::cout << "Player " << winner.getName() << " wins the game!\n";
        std::cout << "Quitting the game...\n";
        throw std::runtime_error("Game ended due to a player winning");
    }

    std::vector<core::Target> GameState::getValidCreatures(
        ExecutionContext exec_ctx, Controller controller) const
    {
        auto &priority_manager{exec_ctx.priority_manager.get()};

        std::vector<core::Target> targets{};
        auto starting_player_id{priority_manager.getPlayerWithPriority()};
        auto current_player_id{starting_player_id};

        if (controller == Controller::You || controller == Controller::Any)
        {
            const auto &player{getPlayer(current_player_id)};
            auto creatures{getCreaturesForPlayer(player)};

            targets.insert(targets.end(), creatures.begin(), creatures.end());
        }
        if (controller == Controller::Opponent || controller == Controller::Any)
        {
            current_player_id = getNextPlayerID(current_player_id);
            while (current_player_id != starting_player_id)
            {
                const auto &player{getPlayer(current_player_id)};
                auto creatures{getCreaturesForPlayer(player)};
                targets.insert(targets.end(), creatures.begin(),
                               creatures.end());
                current_player_id = getNextPlayerID(current_player_id);
            }
        }
        return targets;
    }

    std::vector<core::Target> GameState::getValidTargets(
        ExecutionContext exec_ctx, core::TargetType type,
        Controller controller) const
    {
        switch (type)
        {
        case TargetType::Player:
        {
            const auto &players = getPlayers();
            std::vector<Target> targets;
            std::transform(
                players.begin(), players.end(), std::back_inserter(targets),
                [](const Player &player) -> Target { return player.getID(); });
            return targets;
        }
        case TargetType::Creature:
            return getValidCreatures(exec_ctx, controller);
        case TargetType::Permanent:
        {
            std::vector<Target> targets;
            auto starting_player_id{activePlayer().getID()};
            auto current_player_id{starting_player_id};

            while (true)
            {
                const auto &player{getPlayer(current_player_id)};
                const auto &player_permanents =
                    player.battlefield().permanents();
                for (const auto &[permanent_type, permanents] :
                     player_permanents)
                {
                    std::transform(permanents.begin(), permanents.end(),
                                   std::back_inserter(targets),
                                   [](const Permanent &perm) -> Target
                                   { return perm; });
                }
                current_player_id = getNextPlayerID(current_player_id);
                if (current_player_id == starting_player_id)
                {
                    break;
                }
            }
            return targets;
        }
        case TargetType::Land:
        case TargetType::Planeswalker:
        case TargetType::Card:
        case TargetType::Any:
        case TargetType::Spell:
        {
            std::vector<Target> targets{};
            for (const auto &object : stack().getStackObjects())
            {
                if (std::holds_alternative<CardID>(object))
                {
                    targets.emplace_back(std::get<CardID>(object));
                }
            }
            return targets;
        }
        default:
            throw std::runtime_error("getValidTargets for type " +
                                     targetTypeToString(type) +
                                     " is not implemented yet");
        }
    }

    void GameState::moveCardFromZone(Player &player, const Card &card)
    {
        std::cout << "Removing " << card.getID().getID()
                  << " from zone: " << card.getZone() << '\n';
        switch (card.getZone())
        {
        case Zone::HAND:
            player.hand().removeCard(card);
            break;
        case Zone::LIBRARY:
            library().removeCard(card);
            break;
        case Zone::BATTLEFIELD:
            player.battlefield().removeCard(card);
            break;
        case Zone::GRAVEYARD:
            graveyard().removeCard(card);
            break;
        case Zone::EXILE:
            exile().removeCard(card);
            break;
        case Zone::STACK:
            // while it is called a stack and it does have FILO properties cards
            // can be removed at any level
            stack().removeObject(card.getID());
            break;
        }
    }

    void GameState::moveCardToZone(Card &card, Player &player, Zone zone)
    {
        switch (zone)
        {
        case Zone::LIBRARY:
            m_library.addCardTop(card);
            break;
        case Zone::HAND:
            player.hand().addCard(card);
            break;
        case Zone::BATTLEFIELD:
            player.battlefield().addCard(card);
            break;
        case Zone::GRAVEYARD:
            m_graveyard.addCard(card);
            break;
        case Zone::EXILE:
            m_exile.addCard(card);
            break;
        case Zone::STACK:
            m_stack.push(card.getID());
            break;
        }
    }

    void GameState::clearScreen()
    {
        std::cout << std::string(CLEAR_SCREEN_LINES, '\n');
    }

    void GameState::render(const CardRegistry &card_registry) const
    {
        // Render the full TUI
        clearScreen();

        // opponnet life total and mana pool
        std::cout << nonActivePlayer().getName()
                  << "'s Life Total: " << nonActivePlayer().getLifeTotal()
                  << '\n';
        std::cout << nonActivePlayer().getName() << "'s Mana Pool: ";
        std::cout << nonActivePlayer().manaPool() << "\n";
        std::cout << "\n";

        // opponents hand (top)`
        std::cout << nonActivePlayer().getName() << "'s Hand: ";
        printCards(nonActivePlayer().hand().getCards(), card_registry);
        std::cout << "\n";

        // Opponents player's lands
        std::cout << nonActivePlayer().getName() << "'s Lands: ";
        printCards(nonActivePlayer().battlefield().getLands(), card_registry);
        std::cout << "\n";

        // Opponent's battlefield
        std::cout << nonActivePlayer().getName() << "'s Creatures: ";
        printCards(nonActivePlayer().battlefield().getCreatures(),
                   card_registry);
        std::cout << "\n\n"; // space between battlefields

        // Active player's creatures
        std::cout << activePlayer().getName() << "'s Creatures: ";
        printCards(activePlayer().battlefield().getCreatures(), card_registry);
        std::cout << "\n";

        // Active player's lands
        std::cout << activePlayer().getName() << "'s Lands: ";
        printCards(activePlayer().battlefield().getLands(), card_registry);
        std::cout << "\n";

        // Active player's hand
        std::cout << activePlayer().getName() << "'s Hand: ";
        printCards(activePlayer().hand().getCards(), card_registry);
        std::cout << "\n";

        // active player life total and mana pool
        std::cout << activePlayer().getName() << "'s Mana Pool: ";
        std::cout << activePlayer().manaPool() << "\n";
        std::cout << activePlayer().getName()
                  << "'s Life Total: " << activePlayer().getLifeTotal() << '\n';
        std::cout << "\n";

        std::cout << "Cards in library: " << library().getCards().size()
                  << "\n";
        std::cout << "Graveyard: ";
        printCards(graveyard().getCards(), card_registry);
        std::cout << "Stack: ";
        const auto &stack_objects = stack().getStackObjects();
        for (const auto &object : stack_objects)
        {
            std::visit(
                utils::overloaded{[&card_registry](const CardID &card_id)
                                  {
                                      const auto *card = card_registry[card_id];
                                      std::cout << card->getData().name
                                                << " (Card)\n";
                                  },
                                  [](const abilities::BoundAbility &ability)
                                  {
                                      std::cout
                                          << ability.definition().display()
                                          << " (Ability)\n";
                                  }},
                object);
        }
        std::cout << "\n";
    }
} // namespace dandan::core
