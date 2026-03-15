#include "dandan/Card.h"
#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

int main()
{
    const std::filesystem::path jsonPath =
        std::filesystem::path{DANDAN_SOURCE_DIR} / "data" / "jsons" / "Island.json";

    std::ifstream jsonFile{jsonPath};
    if (!jsonFile.is_open())
    {
        std::cerr << "Failed to open JSON file: " << jsonPath << '\n';
        return 1;
    }

    nlohmann::json j;
    try
    {
        jsonFile >> j;
    }
    catch (const nlohmann::json::parse_error &e)
    {
        std::cerr << "Failed to parse JSON file: " << jsonPath << " (" << e.what() << ")\n";
        return 1;
    }

    Card card{j.get<Card>()};
    std::cout << card << '\n';
    return 0;
}