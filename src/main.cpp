#include "dandan/Card.h"
#include "dandan/WithDamage.h"
#include "dandan/ManaAbility.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{

    // TODO: Improve JSON format by using class_name to key the resultant object

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

    namespace fs = std::filesystem;
    const fs::path json_dir = fs::path{DANDAN_SOURCE_DIR} / "data" / "jsons";

    std::error_code ec;
    fs::create_directories(json_dir, ec);
    if (ec)
    {
        std::cerr << "Failed to create directory: " << json_dir << " (" << ec.message() << ")\n";
        return 1;
    }

    const auto card_path = [json_dir](std::string_view card_name)
    {
        fs::path filename{std::string(card_name)};
        filename.replace_extension(".json");
        return json_dir / filename;
    };

    const fs::path island_json_path = card_path(Island.get_name());
    std::ofstream island_json_file{island_json_path};
    if (!island_json_file.is_open())
    {
        std::cerr << "Failed to open file: " << island_json_path << '\n';
        return 1;
    }
    const nlohmann::json island_json = Island;
    island_json_file << island_json.dump(4) << '\n';

    const fs::path shivan_reef_json_path = card_path(shivan_reef.get_name());
    std::ofstream shivan_reef_json_file{shivan_reef_json_path};
    if (!shivan_reef_json_file.is_open())
    {
        std::cerr << "Failed to open file: " << shivan_reef_json_path << '\n';
        return 1;
    }
    const nlohmann::json shivan_reef_json = shivan_reef;
    shivan_reef_json_file << shivan_reef_json.dump(4) << '\n';
}