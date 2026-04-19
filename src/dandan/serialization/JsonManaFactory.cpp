#ifdef DANDAN_BUILD_SERIALIZE
#include "dandan/serialization/JsonManaFactory.h"
#include "dandan/mana/Mana.h"
#include <algorithm>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<dandan::mana::ManaList>::create_json(
        const dandan::mana::ManaList *mana)
    {
        nlohmann::json j = nlohmann::json::array();
        std::transform(mana->getOptions().begin(), mana->getOptions().end(),
                       std::back_inserter(j),
                       [](const auto &option)
                       {
                           return JsonFactory<dandan::mana::Mana>::create_json(
                               option.get());
                       });
        return j;
    }

    std::unique_ptr<dandan::mana::ManaList> JsonFactory<
        dandan::mana::ManaList>::create_product(const nlohmann::json &j)
    {
        std::vector<std::unique_ptr<dandan::mana::Mana>> options{};
        std::transform(
            j.begin(), j.end(), std::back_inserter(options),
            [](const auto &option_json)
            {
                return JsonFactory<dandan::mana::Mana>::create_product(
                    option_json);
            });
        return std::make_unique<dandan::mana::ManaList>(std::move(options));
    }

    nlohmann::json JsonFactory<dandan::mana::Mana>::create_json(
        const dandan::mana::Mana *mana)
    {
        return ManaToSymbols(mana->getMana());
    }

    std::unique_ptr<dandan::mana::Mana> JsonFactory<
        dandan::mana::Mana>::create_product(const nlohmann::json &j)
    {
        const std::string mana_str = j.get<std::string>();
        auto mana = std::make_unique<dandan::mana::Mana>();

        for (std::size_t i = 0; i < mana_str.size(); ++i)
        {
            const char c = mana_str[i];
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
            case '(':
            {
                const auto close_pos = mana_str.find(')', i);
                if (close_pos == std::string::npos)
                {
                    throw std::runtime_error("Invalid mana string in JSON: "
                                             "missing closing parenthesis");
                }

                const std::string generic_amount_str =
                    mana_str.substr(i + 1, close_pos - (i + 1));
                const int generic_amount = std::stoi(generic_amount_str);
                mana->getMana()[dandan::mana::ManaType::GENERIC] +=
                    generic_amount;

                // Move iterator to ')' so loop increment goes to next symbol.
                i = close_pos;
                break;
            }
            default:
                throw std::runtime_error("Unknown mana symbol in JSON: " +
                                         std::string(1, c));
            }
        }

        return mana;
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE