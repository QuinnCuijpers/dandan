#include "dandan/mana/ManaBag.h"
#include "dandan/mana/ManaPrice.h"
#include "dandan/mana/ManaType.h"
#include "dandan/serialization/JsonFactory.h"
#include <cstddef>
#include <string>
#ifdef DANDAN_SERIALIZE
#include <algorithm>
#include <nlohmann/json.hpp>

namespace dandan::serialization
{
    nlohmann::json JsonFactory<dandan::mana::ManaList>::create_json(
        const dandan::mana::ManaList &mana)
    {
        nlohmann::json json = nlohmann::json::array();
        std::transform(
            mana.getOptions().begin(), mana.getOptions().end(),
            std::back_inserter(json),
            [](const auto &option)
            {
                return JsonFactory<dandan::mana::ManaBag>::create_json(&option);
            });
        return json;
    }

    dandan::mana::ManaList JsonFactory<dandan::mana::ManaList>::create_product(
        const nlohmann::json &json)
    {
        std::vector<mana::ManaBag> options{};
        std::transform(
            json.begin(), json.end(), std::back_inserter(options),
            [](const auto &option_json)
            {
                return JsonFactory<dandan::mana::ManaBag>::create_product(
                    option_json);
            });
        return dandan::mana::ManaList(std::move(options));
    }

    nlohmann::json JsonFactory<dandan::mana::ManaPrice>::create_json(
        const dandan::mana::ManaPrice *mana)
    {
        auto specific = mana::ManaBag::ManaToSymbols(mana->specific());
        std::string generic = mana->generic() > 0
                                  ? "(" + std::to_string(mana->generic()) + ")"
                                  : "";

        auto cost{generic + specific};

        return !cost.empty() ? cost : "(0)";
    }

    dandan::mana::ManaPrice JsonFactory<
        dandan::mana::ManaPrice>::create_product(const nlohmann::json &json)
    {
        const std::string mana_str = json.get<std::string>();
        auto specific_mana = mana::ManaBag{};
        size_t generic_amount{};

        for (std::size_t i = 0; i < mana_str.size(); ++i)
        {
            const char char_ = mana_str[i];
            switch (char_)
            {
            case 'C':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::COLORLESS, 1}});
                continue;
            case 'W':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::WHITE, 1}});
                continue;
            case 'U':
                specific_mana =
                    specific_mana.add(mana::ManaBag{{mana::ManaType::BLUE, 1}});
                continue;
            case 'B':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::BLACK, 1}});
                continue;
            case 'R':
                specific_mana =
                    specific_mana.add(mana::ManaBag{{mana::ManaType::RED, 1}});
                continue;
            case 'G':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::GREEN, 1}});
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
                generic_amount = std::stoi(generic_amount_str);

                // Move iterator to ')' so loop increment goes to next
                // symbol.
                i = close_pos;
                continue;
            }
            default:
                throw std::runtime_error("Unknown mana symbol in JSON: " +
                                         std::string(1, char_));
            }
        }
        return mana::ManaPrice{specific_mana, generic_amount};
    }

    nlohmann::json JsonFactory<dandan::mana::ManaBag>::create_json(
        const dandan::mana::ManaBag *mana)
    {
        return mana::ManaBag::ManaToSymbols(*mana);
    }

    dandan::mana::ManaBag JsonFactory<dandan::mana::ManaBag>::create_product(
        const nlohmann::json &json)
    {
        const std::string mana_str = json.get<std::string>();
        auto specific_mana = mana::ManaBag{};

        for (char char_ : mana_str)
        {
            switch (char_)
            {
            case 'C':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::COLORLESS, 1}});
                continue;
            case 'W':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::WHITE, 1}});
                continue;
            case 'U':
                specific_mana =
                    specific_mana.add(mana::ManaBag{{mana::ManaType::BLUE, 1}});
                continue;
            case 'B':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::BLACK, 1}});
                continue;
            case 'R':
                specific_mana =
                    specific_mana.add(mana::ManaBag{{mana::ManaType::RED, 1}});
                continue;
            case 'G':
                specific_mana = specific_mana.add(
                    mana::ManaBag{{mana::ManaType::GREEN, 1}});
                continue;

            default:
                throw std::runtime_error("Unknown mana symbol in JSON: " +
                                         std::string(1, char_));
            }
        }
        return specific_mana;
    }
} // namespace dandan::serialization

#endif // DANDAN_SERIALIZE
