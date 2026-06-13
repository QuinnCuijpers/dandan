#include "dandan/effects/one_shot/MindBendEffect.h"
#include "dandan/core/ColorWord.h"
#include "dandan/utils/overloadVisitor.h"
#include "dandan/utils/stringToBasicLandType.h"
#include "dandan/utils/stringToColorWord.h"
#include <variant>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> MindBendEffect::apply_impl(
        [[maybe_unused]] core::Game &game) const
    {
        auto target{m_target};

        if (std::get_if<core::Permanent>(&target) == nullptr)
        {
            throw std::runtime_error(
                "Invalid target for Mind Bend: target must be a permanent");
        }

        auto permanent{std::get<core::Permanent>(target)};
        auto *card{game.getCardByID(permanent)};

        // Change the text of target permanent by replacing all instances of one
        // color word with another or one basic land type with another.
        std::cout << display() << '\n';
        std::cout << "color word or basic land type to replace: ";
        std::string to_replace;
        std::getline(game.istream(), to_replace);

        core::ReplacementType to_replace_var;

        auto to_replace_type{utils::stringToBasicLandType(to_replace)};
        if (to_replace_type == core::SubType::None)
        {
            auto to_replace_color{utils::stringToColorWord(to_replace)};
            to_replace_var = to_replace_color;
        }
        else
        {
            to_replace_var = to_replace_type;
        }

        std::cout << "color word or basic land type to replace with: ";

        std::visit(
            utils::overloaded{
                [&game, &card](const core::ColorWord to_replace_color)
                {
                    std::cout << "color word to replace with: ";
                    std::string replace_with_color_str;
                    std::getline(game.istream(), replace_with_color_str);
                    auto replace_with_color{
                        utils::stringToColorWord(replace_with_color_str)};
                    if (replace_with_color == core::ColorWord::None)
                    {
                        throw std::runtime_error("Invalid color word: " +
                                                 replace_with_color_str);
                    }
                    card->replaceText(to_replace_color, replace_with_color);
                },
                [&game, &card](const core::SubType to_replace_basic)
                {
                    std::cout << "basic land type to replace with: ";
                    std::string replace_with_basic_str;
                    std::getline(game.istream(), replace_with_basic_str);
                    auto replace_with_basic{
                        utils::stringToBasicLandType(replace_with_basic_str)};
                    if (replace_with_basic == core::SubType::None)
                    {
                        throw std::runtime_error("Invalid basic land type: " +
                                                 replace_with_basic_str);
                    }
                    card->replaceText(to_replace_basic, replace_with_basic);
                },
            },
            to_replace_var);

        return nullptr;
    }
} // namespace dandan::effects