#include "dandan/effects/DrawEffect.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::effects
{

    void DrawEffect::apply()
    {
        std::cout << "Applying draw effect\n";
    }

    // TODO: implement from_json factory
    void DrawEffect::from_json(const nlohmann::json &j, IEffect &effect)
    {
    }

    void DrawEffect::to_json(nlohmann::json &j, const IEffect &effect)
    {
        auto draw_effect{dynamic_cast<const DrawEffect &>(effect)};
        j = nlohmann::json{
            {"type", "DrawEffect"},
            {"data", nlohmann::json{}}};
        j["data"]["amount"] = draw_effect.m_amount;
    }
}