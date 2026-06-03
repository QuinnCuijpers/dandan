#include "dandan/core/phases/MainPhase.h"
#include "dandan/abilities/AbilityContext.h"
#include "dandan/core/Game.h"
#include "dandan/core/actions/ActivateAbilityAction.h"
#include "dandan/core/actions/PlayCardAction.h"
#include "dandan/core/phases/CombatPhase.h"
#include "dandan/core/phases/EndingPhase.h"
#include <cstddef>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace dandan::core
{
    MainPhase::MainPhase(Game &game)
        : IPhase(game), m_next_phase(std::make_unique<CombatPhase>(game))
    {
    }

    MainPhase::MainPhase(Game &game, bool pre_combat)
        : IPhase(game), m_pre_combat_main_phase(pre_combat)
    {
        if (!m_pre_combat_main_phase)
        {
            m_next_phase = std::make_unique<EndingPhase>(game);
        }
        else
        {
            m_next_phase = std::make_unique<CombatPhase>(game);
        }
    }

    [[nodiscard]] std::unique_ptr<IPhase> MainPhase::handle()
    {
        std::cout << "Handling " << name() << '\n';
        game().priorityManager().setPriorityToActivePlayer(game());
        while (true)
        {
            game().render();
            std::cout << "What do you want to do? (play [card index], activate "
                         "[card index], pass, next "
                         "or quit) ";
            std::string input;
            std::getline(game().istream(), input);
            if (input == "pass")
            {
                std::cout << "Passing turn\n";
                m_next_phase = std::make_unique<EndingPhase>(game());
                break;
            }
            if (input == "quit")
            {
                std::cout << "Quitting game\n";
                throw std::runtime_error("Game quit by user");
            }
            if (input == "next")
            {
                if (m_pre_combat_main_phase)
                {
                    m_next_phase = std::make_unique<CombatPhase>(game());
                }
                else
                {
                    std::cout << "you can't go back to combat phase\n";
                }
                break;
            }
            if (input.rfind("play ", 0) == 0)
            {
                handlePlay(input);
                continue;
            }
            if (input.rfind("activate ", 0) == 0)
            {
                handleActivate(input);
                continue;
            }
            // TODO: improve error handling for invalid input
            throw std::invalid_argument(
                "Invalid input: " + (input.empty() ? input : "empty input"));
        }
        return std::move(m_next_phase);
    }

    void MainPhase::handlePlay(const std::string &input)
    {

        int card_id = std::stoi(input.substr(std::size("play ") - 1));

        // does not move the card out of the previous zone
        auto action =
            std::make_unique<PlayCardAction>(CardID::fromInt(card_id));

        if (game().isActionPrevented(*action))
        {
            std::cout << "Action prevented\n";
            return;
        }

        auto effect{action->createEffect(game())};
        const auto &final_effect{
            game().replacementManager().applyReplacementEffects(*effect,
                                                                game())};

        auto event{final_effect->apply(game())};
        game().eventManager().notify(*event, game());
    }

    void MainPhase::handleActivate(const std::string &input)
    {
        int card_id = std::stoi(input.substr(std::size("activate ") - 1));

        // does not move the card out of the previous zone
        auto *cardp{game().getCardByID(card_id)};

        if (cardp->getZone() != Zone::BATTLEFIELD &&
            cardp->getZone() != Zone::HAND)
        {
            std::cout << "Card is not on the battlefield or in hand\n";
            return;
        }

        size_t ability_index{};
        int display_index{};

        const auto &abilities = cardp->getData().getAbilities();

        auto ability_indices{
            std::vector<std::pair<size_t, std::optional<size_t>>>{}};

        auto base_ability_context{abilities::AbilityContext{
            cardp->getID(), cardp->getControllerID()}};

        for (const auto &ability : cardp->getData().getAbilities())
        {
            if (!ability->canActivate(game(), base_ability_context))
            {
                ++ability_index;
                continue;
            }
            // TODO: decorator types dont split correctly
            if (ability->optionsAmount() > 1)
            {
                size_t modal_index{};
                for (size_t option_index{};
                     option_index < ability->optionsAmount(); ++option_index)
                {
                    std::cout << "Ability " << display_index++ << ": ";
                    std::cout << ability->displayOption(option_index);
                    std::cout << ".\n";
                    ability_indices.emplace_back(ability_index, modal_index);
                    ++modal_index;
                }
            }
            else
            {
                std::cout << "Ability " << display_index++ << ": "
                          << ability->display();
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
            std::getline(game().istream(), ability_input);
            size_t ability_index_input = std::stoull(ability_input);
            if (ability_index_input >= ability_indices.size())
            {
                std::cout << "Invalid ability index\n";
                return;
            }
            real_index = ability_indices[ability_index_input].first;
            modal_index_opt = ability_indices[ability_index_input].second;
        }

        const auto *ability = abilities[real_index].get();

        auto ability_context{abilities::AbilityContext{
            cardp->getID(), cardp->getControllerID(), modal_index_opt}};

        auto action =
            std::make_unique<ActivateAbilityAction>(ability, ability_context);

        if (game().isActionPrevented(*action))
        {
            std::cout << "Action prevented\n";
            return;
        }

        auto effect{action->createEffect(game())};
        std::cout << "Created effect for ability activation\n";
        const auto &final_effect{
            game().replacementManager().applyReplacementEffects(*effect,
                                                                game())};

        auto event{final_effect->apply(game())};
        if (event)
        {
            game().eventManager().notify(*event, game());
        }
    }

} // namespace dandan::core