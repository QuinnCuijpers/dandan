#include "dandan/dandan.h"

#include <iostream>

#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/abilities/StaticAbility.h"
#include "dandan/conditions/ControlsIslandCondition.h"
#include "dandan/effects/continuous/prevention/AttackPreventionEffect.h"
#include "dandan/effects/one_shot/SelfSacrificeEffect.h"
#include "dandan/events/NoIslandsEvent.h"
#include <exception>
#include <filesystem>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>
#endif

#ifdef DANDAN_BUILD_SERIALIZE
namespace
{
    std::filesystem::path project_root()
    {
        return std::filesystem::path{DANDAN_PROJECT_SOURCE};
    }

    std::filesystem::path resolve_from_project_root(
        const std::filesystem::path &path)
    {
        if (path.is_absolute())
        {
            return path;
        }
        return project_root() / path;
    }
    std::filesystem::path get_card_path(const std::filesystem::path &json_dir,
                                        std::string_view card_name)
    {
        std::filesystem::path filename{std::string(card_name)};
        filename.replace_extension(".json");
        return resolve_from_project_root(json_dir) / filename;
    }
} // namespace
#endif

#ifdef DANDAN_BUILD_SERIALIZE
dandan::Card read_Card_from_json(const std::filesystem::path &json_path)
{
    const auto resolved_path = resolve_from_project_root(json_path);
    std::ifstream json_file{resolved_path};
    if (!json_file.is_open())
    {
        throw std::runtime_error("Failed to open JSON file: " +
                                 resolved_path.string());
    }

    nlohmann::json json;
    try
    {
        json_file >> json;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        throw std::runtime_error(
            "Failed to parse JSON file: " + resolved_path.string() + " (" +
            e.what() + ")");
    }

    return json.get<dandan::Card>();
}

void write_card_to_json(const dandan::Card &card,
                        const std::filesystem::path &json_path)
{
    const auto resolved_path = resolve_from_project_root(json_path);
    std::filesystem::create_directories(resolved_path.parent_path());

    std::ofstream json_file{resolved_path};
    if (!json_file.is_open())
    {
        throw std::runtime_error("Failed to open JSON file for writing: " +
                                 resolved_path.string());
    }

    nlohmann::json json = card;
    json_file << json.dump(4) << '\n';
}

void check_card_serialize()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>()};

    abilities.emplace_back(std::make_unique<dandan::TriggeredAbility>(
        std::make_unique<dandan::events::NoIslandsEvent>(),
        std::make_unique<dandan::effects::SelfSacrificeEffect>()));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        dandan::abilities::StaticAbility::Prevention,
        std::make_unique<dandan::effects::AttackPreventionEffect>(
            std::make_unique<dandan::conditions::ControlsIslandCondition>())));

    dandan::Card test{"Dandan",
                      std::make_unique<dandan::BlueMana>(2),
                      dandan::Card::Creature,
                      dandan::Card::SubType::Fish,
                      std::move(abilities),
                      dandan::Stats{4, 1}};

    std::cout << test << '\n';

    const auto card_json_path = get_card_path("data/jsons", test.getName());
    try
    {
        write_card_to_json(test, card_json_path);
        const auto loaded_card = read_Card_from_json(card_json_path);
        std::cout << loaded_card << '\n';
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}
#endif

int main()
{
#ifdef DANDAN_BUILD_SERIALIZE
    check_card_serialize();
#endif

    [[maybe_unused]] auto game = dandan::core::Game{};
    // game.printCards();
    // auto &active_player = game.getActivePlayer();
    // for (int i{}; i < STARTING_HAND_SIZE; ++i)
    // {
    //     active_player.playCard(0);
    // }

    // game.printCards();
    std::cout << "Hello, Dandan!\n";
    game.run();
}