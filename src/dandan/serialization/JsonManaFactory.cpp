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
        nlohmann::json json = nlohmann::json::array();
        std::transform(mana->getOptions().begin(), mana->getOptions().end(),
                       std::back_inserter(json),
                       [](const auto &option)
                       {
                           return JsonFactory<dandan::mana::Mana>::create_json(
                               option.get());
                       });
        return json;
    }

    std::unique_ptr<dandan::mana::ManaList> JsonFactory<
        dandan::mana::ManaList>::create_product(const nlohmann::json &json)
    {
        std::vector<std::unique_ptr<dandan::mana::Mana>> options{};
        std::transform(
            json.begin(), json.end(), std::back_inserter(options),
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
        dandan::mana::Mana>::create_product(const nlohmann::json &json)
    {
        const std::string mana_str = json.get<std::string>();
        auto mana = std::make_unique<dandan::mana::Mana>();

        for (std::size_t i = 0; i < mana_str.size(); ++i)
        {
            const char char_ = mana_str[i];
            switch (char_)
            {
            case 'C':
                mana->addMana(mana::ManaType::COLORLESS, 1);
                continue;
            case 'W':
                mana->addMana(mana::ManaType::WHITE, 1);
                continue;
            case 'U':
                mana->addMana(mana::ManaType::BLUE, 1);
                continue;
            case 'B':
                mana->addMana(mana::ManaType::BLACK, 1);
                continue;
            case 'R':
                mana->addMana(mana::ManaType::RED, 1);
                continue;
            case 'G':
                mana->addMana(mana::ManaType::GREEN, 1);
                continue;
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
                mana->addMana(mana::ManaType::GENERIC, generic_amount);

                // Move iterator to ')' so loop increment goes to next symbol.
                i = close_pos;
                continue;
            }
            default:
                throw std::runtime_error("Unknown mana symbol in JSON: " +
                                         std::string(1, char_));
            }
        }
        return mana;
    }
} // namespace dandan::serialization

#endif // DANDAN_BUILD_SERIALIZE