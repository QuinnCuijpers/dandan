#include "dandan/core/Board.h"
#include "dandan/dandan.h"

#include <filesystem>
#include <iostream>
#include <memory>

#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/mana/AndMana.h"
#include "dandan/mana/BlueMana.h"
#include <exception>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#endif

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
} // namespace

std::filesystem::path get_card_path(const std::filesystem::path &json_dir,
                                    std::string_view card_name);
void print_card_info(const dandan::Card &card);

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

    nlohmann::json j;
    try
    {
        json_file >> j;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        throw std::runtime_error(
            "Failed to parse JSON file: " + resolved_path.string() + " (" +
            e.what() + ")");
    }

    return j.get<dandan::Card>();
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

    nlohmann::json j = card;
    json_file << j.dump(4) << '\n';
}

void check_card_serialize()
{
    auto abilities{std::vector<std::unique_ptr<dandan::IAbility>>{}};

    abilities.emplace_back(std::make_unique<dandan::ManaAbility>(
        dandan::ManaList{std::make_unique<dandan::mana::AndMana>(
            std::make_unique<dandan::mana::BlueMana>(),
            std::make_unique<dandan::mana::RedMana>())}));

    abilities.emplace_back(std::make_unique<dandan::StaticAbility>(
        std::make_unique<dandan::ETBEffect>(),
        std::make_unique<dandan::EntersTappedEffect>()));

    dandan::Card test{"Izzet Boilerworks", 0, dandan::Card::Land,
                      std::move(abilities)};

    print_card_info(test);

    const auto card_json_path = get_card_path("data/jsons", test.getName());
    try
    {
        write_card_to_json(test, card_json_path);
        const auto loaded_card = read_Card_from_json(card_json_path);
        print_card_info(loaded_card);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << '\n';
    }
}
#endif

std::filesystem::path get_card_path(const std::filesystem::path &json_dir,
                                    std::string_view card_name)
{
    std::filesystem::path filename{std::string(card_name)};
    filename.replace_extension(".json");
    return resolve_from_project_root(json_dir) / filename;
}

void print_card_info(const dandan::Card &card)
{
    std::cout << "Card: " << card.getName() << '\n';
    std::cout << "Cost: " << card.getCost() << '\n';
    std::cout << "Type: " << card.TypeToString(card.getType()) << '\n';
    std::cout << "Abilities:\n";
    for (const auto &ability : card.getAbilities())
    {
        ability->resolve();
    }
}

int main()
{
    dandan::core::Board board{};

    board.printCards();
}