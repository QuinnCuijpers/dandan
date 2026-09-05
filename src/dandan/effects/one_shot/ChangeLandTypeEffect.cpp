#include "dandan/effects/one_shot/ChangeLandTypeEffect.h"
#include "dandan/core/GameState.h"
#include "dandan/utils/stringToBasicLandType.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <tuple>

namespace dandan::effects
{
    std::unique_ptr<events::IEvent> ChangeLandTypeEffect::apply_impl(
        core::ExecutionContext exec_ctx) const
    {
        auto &game{exec_ctx.state.get()};
        auto &card_registry{exec_ctx.cards.get()};
        auto &istream{exec_ctx.input_manager.get().stream()};

        // FIXME: technically it should be able to call any land type, but we
        // only have basic land types in dandan

        auto basic_land_1 = m_basic_land_1;
        auto basic_land_2 = m_basic_land_2;

        if (!m_basic_land_1.has_value() && !m_basic_land_2.has_value())
        {
            std::cout
                << "Choose a basic land type and a basic land type. Each "
                   "land of the first chosen type becomes the second chosen "
                   "type until end of turn. \n";
        }
        if (!m_basic_land_1.has_value())
        {
            std::cout << "First choice (basic land type): ";
            std::string land_type_input;
            std::getline(istream, land_type_input);
            basic_land_1 = utils::stringToBasicLandType(land_type_input);
        }
        if (!m_basic_land_2.has_value())
        {
            std::cout << "Second choice (basic land type): ";
            std::string new_land_type_input;
            std::getline(istream, new_land_type_input);
            basic_land_2 = utils::stringToBasicLandType(new_land_type_input);
        }

        for (const auto &card_id : card_registry.card_ids())
        {
            auto *card{card_registry[card_id]};

            auto subtypes{card->getCurrentSubTypes()};
            std::ignore = std::any_of(subtypes.begin(), subtypes.end(),
                                      [&](const auto subtype)
                                      {
                                          if (subtype == basic_land_1)
                                          {
                                              card->setCurrentSubTypes(
                                                  {basic_land_2.value()});
                                              return true;
                                          }
                                          return false;
                                      });
        }

        game.addEndOfTurnEffect(std::make_unique<ChangeLandTypeEffect>(
            basic_land_2.value(), basic_land_1.value(), getEffectContext()));

        return nullptr;
    }
} // namespace dandan::effects
