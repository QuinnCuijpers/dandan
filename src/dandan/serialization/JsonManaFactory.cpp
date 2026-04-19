#include "dandan/serialization/JsonManaFactory.h"
#ifdef DANDAN_BUILD_SERIALIZE
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<dandan::mana::ManaList>::create_json(
        const dandan::mana::ManaList *mana)
    {
        nlohmann::json j = nlohmann::json::array();
        for (const auto &option : mana->getOptions())
        {
            j.push_back(JsonFactory<dandan::mana::Mana>::create_json(*option));
        }
        return j;
    }

    std::unique_ptr<dandan::mana::ManaList> JsonFactory<
        dandan::mana::ManaList>::create_product(const nlohmann::json &j)
    {
        std::vector<std::unique_ptr<dandan::mana::Mana>> options{};
        for (const auto &option_json : j)
        {
            options.push_back(
                JsonFactory<dandan::mana::Mana>::create_product(option_json));
        }
        return std::make_unique<dandan::mana::ManaList>(std::move(options));
    }

    nlohmann::json JsonFactory<dandan::mana::Mana>::create_json(
        const dandan::mana::Mana &mana)
    {
        return ManaToSymbols(mana.getMana());
    }

    std::unique_ptr<dandan::mana::Mana> JsonFactory<
        dandan::mana::Mana>::create_product(const nlohmann::json &j)
    {
        std::string mana_str = j.get<std::string>();
        auto mana = std::make_unique<dandan::mana::Mana>();
        for (char c : mana_str)
        {
            switch (c)
            {
            case 'C':
                mana->getMana()[dandan::mana::ManaType::COLORLESS]++;
                break;
            case 'W':
                mana->getMana()[dandan::mana::ManaType::WHITE]++;
                break;
            case 'U':
                mana->getMana()[dandan::mana::ManaType::BLUE]++;
                break;
            case 'B':
                mana->getMana()[dandan::mana::ManaType::BLACK]++;
                break;
            case 'R':
                mana->getMana()[dandan::mana::ManaType::RED]++;
                break;
            case 'G':
                mana->getMana()[dandan::mana::ManaType::GREEN]++;
                break;
            default:
                throw std::runtime_error("Unknown mana symbol in JSON: " +
                                         std::string(1, c));
            }
        }
        return mana;
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE