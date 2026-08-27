#include "dandan/core/Game.h"
#include "dandan/conditions/PlayedLandCondition.h"
#include "dandan/conditions/StartingPlayerCondition.h"
#include "dandan/core/ExecutionContext.h"
#include "dandan/core/Player.h"
#include "dandan/core/Target.h"
#include "dandan/core/TargetRequirement.h"
#include "dandan/core/actions/ActivateAbilityAction.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/core/phases/BeginningPhase.h"
#include "dandan/effects/continuous/prevention/DrawPreventionEffect.h"
#include "dandan/effects/continuous/prevention/PlayCardPreventionEffect.h"
#include "dandan/utils/log.h"
#include "dandan/utils/overloadVisitor.h"
#include <algorithm>
#include <deque>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

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

    void Game::GameSetup(bool shuffle)
    {
        for (auto card_id : m_card_registry.card_ids())
        {
            auto *card = m_card_registry[card_id];
            std::cout << "adding Card id: " << card->getID() << '\n';
            m_library.addCardBottom(*card);
        }

        if (shuffle)
        {
            m_library.shuffle();
        }

        auto one_land_a_turn{
            std::make_unique<effects::PlayCardPreventionEffect>(
                std::make_unique<conditions::PlayedLandCondition>())};

        // Randomize whom is starting player
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<> dist(0, AMOUNT_PLAYERS - 1);

        int starting_player_index = dist(gen);
        m_active_player_index = starting_player_index;

        auto no_draw_starting_player{
            std::make_unique<effects::DrawPreventionEffect>(
                std::make_unique<conditions::StartingPlayerCondition>())};

        m_prevention_manager.subscribe(activePlayer().getID(),
                                       std::move(no_draw_starting_player));
        m_prevention_manager.subscribe(std::move(one_land_a_turn));

        DLOGI << "Active player: " << activePlayer().getName() << '\n';
        DLOGI << "Non-active player: " << nonActivePlayer().getName() << '\n';

        for (int i{}; i < STARTING_HAND_SIZE; ++i)
        {
            activePlayer().drawCard({*this, m_card_registry});
            nonActivePlayer().drawCard({*this, m_card_registry});
        }
        // TODO: Implement mulligan rules
        DLOGI << "Game constructed\n";

        DLOGI << "Changing phase to beginning phase\n";
        changePhase(std::make_unique<BeginningPhase>(
            (ExecutionContext{*this, m_card_registry})));
    }
#ifdef DANDAN_SERIALIZE
    Game::Game(const std::filesystem::path &path)
    {
        m_card_registry.load_cards(path);
        GameSetup();
    }
#endif

    Game::Game(std::vector<Card> cards, bool shuffle)
    {
        auto moved_cards{std::move(cards)};
        m_card_registry.setCards(moved_cards);
        std::cout << "Game constructed with explicit cards\n";
        GameSetup(shuffle);
    }

    Game::Game(std::istream &input, bool shuffle) : m_input{&input}
    {
        GameSetup(shuffle);
    }

    Game Game::withCards(std::vector<Card> cards, bool shuffle)
    {
        return Game(std::move(cards), shuffle);
    }

    void Game::run()
    {
        try
        {
            while (true)
            {
                while (m_phase != nullptr)
                {
                    render();
                    handlePhase();
                }
                DLOGI << "Passing turn\n";
                m_first_turn = false;
                m_active_player_index =
                    (m_active_player_index + 1) % AMOUNT_PLAYERS;
                changePhase(std::make_unique<BeginningPhase>(
                    ExecutionContext{*this, m_card_registry}));
            }
        }
        catch (const std::runtime_error &e)
        {
            if (std::string(e.what()) == "Game quit by user")
            {
                DLOGI << "Game quit by user\n";
                return;
            }
            std::cout << "Game ended: " << e.what() << '\n';
        }
    }

    void Game::moveCardFromZone(Player &player, const Card &card)
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
        case Zone::STACK:
            // while it is called a stack and it does have FILO properties cards
            // can be removed at any level
            stack().removeObject(card.getID());
            break;
        }
    }

    void Game::moveCardToZone(Card &card, Player &player, Zone zone)
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

    void Game::clearScreen()
    {
        std::cout << std::string(CLEAR_SCREEN_LINES, '\n');
    }

    void Game::render() const
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
        printCards(nonActivePlayer().hand().getCards());
        std::cout << "\n";

        // Opponents player's lands
        std::cout << nonActivePlayer().getName() << "'s Lands: ";
        printCards(nonActivePlayer().battlefield().getLands());
        std::cout << "\n";

        // Opponent's battlefield
        std::cout << nonActivePlayer().getName() << "'s Creatures: ";
        printCards(nonActivePlayer().battlefield().getCreatures());
        std::cout << "\n\n"; // space between battlefields

        // Active player's creatures
        std::cout << activePlayer().getName() << "'s Creatures: ";
        printCards(activePlayer().battlefield().getCreatures());
        std::cout << "\n";

        // Active player's lands
        std::cout << activePlayer().getName() << "'s Lands: ";
        printCards(activePlayer().battlefield().getLands());
        std::cout << "\n";

        // Active player's hand
        std::cout << activePlayer().getName() << "'s Hand: ";
        printCards(activePlayer().hand().getCards());
        std::cout << "\n";

        // active player life total and mana pool
        std::cout << activePlayer().getName() << "'s Mana Pool: ";
        std::cout << activePlayer().manaPool() << "\n";
        std::cout << activePlayer().getName()
                  << "'s Life Total: " << activePlayer().getLifeTotal() << '\n';
        std::cout << "\n";

        std::cout << "Cards in library: " << m_library.getCards().size()
                  << "\n";
        std::cout << "Graveyard: ";
        printCards(graveyard().getCards());
        std::cout << "Stack: ";
        const auto &stack_objects = stack().getStackObjects();
        for (const auto &object : stack_objects)
        {
            std::visit(
                utils::overloaded{
                    [this](const CardID &card_id)
                    {
                        const auto *card = m_card_registry[card_id];
                        std::cout << card->getData().name << " (Card)\n";
                    },
                    [](const abilities::BoundAbility &ability)
                    {
                        std::cout << ability.definition().display()
                                  << " (Ability)\n";
                    }},
                object);
        }
        std::cout << "\n";
    }

    void Game::quit(const Player &player) const
    {
        // Implementation for quitting the game
        // for now we only support 2 players so we can just end the game
        auto winner_id{getNextPlayerID(player.getID())};
        const auto &winner{getPlayer(winner_id)};
        std::cout << "Player " << winner.getName() << " wins the game!\n";
        std::cout << "Quitting the game...\n";
        std::exit(0);
    }

    std::vector<core::Target> Game::getValidTargets(core::TargetType type,
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
            return getValidCreatures(controller);
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
            for (const auto &object : m_stack.getStackObjects())
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

    void Game::handlePlay(const std::string &input)
    {

        ExecutionContext exec_ctx{*this, m_card_registry};
        int card_id = std::stoi(input.substr(std::size("play ") - 1));

        auto action =
            std::make_unique<PlayCardAction>(CardID::fromInt(card_id));

        if (isActionPrevented(*action))
        {
            std::cout << "Action prevented\n";
            return;
        }

        auto effect{action->createEffect(exec_ctx)};
        const auto &final_effect{
            replacementManager().applyReplacementEffects(*effect, exec_ctx)};

        auto event{final_effect->apply({*this, m_card_registry})};
        if (event)
        {
            eventManager().notify(*event, exec_ctx);
        }
    }

    void Game::handleActivate(const std::string &input)
    {
        ExecutionContext exec_ctx{*this, m_card_registry};
        int card_id = std::stoi(input.substr(std::size("activate ") - 1));

        const auto *cardp{m_card_registry[card_id]};

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
            std::getline(istream(), ability_input);
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

        if (isActionPrevented(*action))
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
            replacementManager().applyReplacementEffects(*effect, exec_ctx)};

        auto event{final_effect->apply(exec_ctx)};
        if (event)
        {
            eventManager().notify(*event, exec_ctx);
        }
    }

    std::vector<core::Target> Game::getValidCreatures(
        Controller controller) const
    {
        std::vector<core::Target> targets{};
        auto starting_player_id{m_priority_manager.getPlayerWithPriority()};
        auto current_player_id{starting_player_id};

        if (controller == Controller::You || controller == Controller::Any)
        {
            const auto &player{getPlayer(current_player_id)};
            auto creatures{getCreaturesForPlayer(player)};

            targets.insert(targets.end(), creatures.begin(), creatures.end());
        }
        if (controller == Controller::Opponent || controller == Controller::Any)
        {

            while (true)
            {
                const auto nextPlayer{getNextPlayerID(current_player_id)};
                const auto &player{getPlayer(nextPlayer)};

                auto creatures{getCreaturesForPlayer(player)};

                targets.insert(targets.end(), creatures.begin(),
                               creatures.end());

                current_player_id = getNextPlayerID(current_player_id);
                if (current_player_id == starting_player_id)
                {
                    break;
                }
            }
        }
        return targets;
    }
} // namespace dandan::core
