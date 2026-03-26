#include "dandan/Card.h"
#include "dandan/WithDamage.h"
#include "dandan/ManaAbility.h"
#include "dandan/ReplacementAbility.h"
#include "dandan/TriggeredAbility.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    std::filesystem::path project_root()
    {
        return std::filesystem::path{DANDAN_SOURCE_DIR};
    }

    std::filesystem::path resolve_from_project_root(const std::filesystem::path &path)
    {
        if (path.is_absolute())
        {
            return path;
        }
        return project_root() / path;
    }
} // namespace

Card read_Card_from_json(const std::filesystem::path &json_path)
{
    const auto resolved_path = resolve_from_project_root(json_path);
    std::ifstream json_file{resolved_path};
    if (!json_file.is_open())
    {
        throw std::runtime_error("Failed to open JSON file: " + resolved_path.string());
    }

    nlohmann::json j;
    try
    {
        json_file >> j;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        throw std::runtime_error("Failed to parse JSON file: " + resolved_path.string() + " (" + e.what() + ")");
    }

    return j.get<Card>();
}

void write_card_to_json(const Card &card, const std::filesystem::path &json_path)
{
    const auto resolved_path = resolve_from_project_root(json_path);
    std::filesystem::create_directories(resolved_path.parent_path());

    std::ofstream json_file{resolved_path};
    if (!json_file.is_open())
    {
        throw std::runtime_error("Failed to open JSON file for writing: " + resolved_path.string());
    }

    nlohmann::json j = card;
    json_file << j.dump(4) << '\n';
}

std::filesystem::path get_card_path(const std::filesystem::path &json_dir, std::string_view card_name)
{
    std::filesystem::path filename{std::string(card_name)};
    filename.replace_extension(".json");
    return resolve_from_project_root(json_dir) / filename;
}

void print_card_info(const Card &card)
{
    std::cout << "Card: " << card.get_name() << '\n';
    std::cout << "Cost: " << card.get_cost() << '\n';
    std::cout << "Type: " << card.TypeToString(card.get_type()) << '\n';
    std::cout << "Abilities:\n";
    for (const auto &ability : card.get_abilities())
    {
        ability->resolve();
    }
}

int main()
{
    std::vector<std::unique_ptr<IAbility>> abilities;
    abilities.push_back(std::make_unique<ManaAbility>(ManaAbility::BLUE));
    abilities.push_back(std::make_unique<ReplacementAbility>(std::make_unique<EntersBattlefieldEvent>(),
                                                             std::make_unique<EntersTappedEffect>()));
    abilities.push_back(
        std::make_unique<TriggeredAbility>(
            std::make_unique<EntersBattlefieldEvent>(),
            std::make_unique<PeekEffect>(3)));
    Card halimar_depths{"Halimar Depths", 0, Card::Land, std::move(abilities)};

    const auto card_json_path = get_card_path("data/jsons", halimar_depths.get_name());
    write_card_to_json(halimar_depths, card_json_path);
}