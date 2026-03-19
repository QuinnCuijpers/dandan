#include "dandan/Card.h"
#include "dandan/IAbilityDecorator.h"
#include "dandan/ManaAbility.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{
    // const std::filesystem::path jsonPath =
    //     std::filesystem::path{DANDAN_SOURCE_DIR} / "data" / "jsons" / "ShivanReef.json";

    // std::ifstream jsonFile{jsonPath};
    // if (!jsonFile.is_open())
    // {
    //     std::cerr << "Failed to open JSON file: " << jsonPath << '\n';
    //     return 1;
    // }

    // nlohmann::json j;
    // try
    // {
    //     jsonFile >> j;
    // }
    // catch (const nlohmann::json::parse_error &e)
    // {
    //     std::cerr << "Failed to parse JSON file: " << jsonPath << " (" << e.what() << ")\n";
    //     return 1;
    // }

    std::vector<std::unique_ptr<IAbility>> abilities;
    abilities.push_back(std::make_unique<ManaAbility>(ManaAbility::ManaType::COLORLESS));
    abilities.push_back(std::make_unique<WithDamage>(std::make_unique<ManaAbility>(ManaAbility::ManaType::RED), 1));

    Card shivan_reef{"Shivan Reef", 0, Card::Type::Land, std::move(abilities)};

    std::cout << "Card: " << shivan_reef.get_name() << '\n';
    std::cout << "Cost: " << shivan_reef.get_cost() << '\n';
    std::cout << "Type: " << shivan_reef.TypeToString(shivan_reef.get_type()) << '\n';
    std::cout << "Abilities:\n";
    for (const auto &ability : shivan_reef.get_abilities())
    {
        ability.get()->resolve();
    }

    std::vector<std::unique_ptr<IAbility>> island_abilities;
    island_abilities.push_back(std::make_unique<ManaAbility>(ManaAbility::ManaType::BLUE));
    Card Island{"Island", 0, Card::Type::Land, std::move(island_abilities)};
    std::cout << Island << '\n';
    for (const auto &ability : Island.get_abilities())
    {
        ability.get()->resolve();
    }
}