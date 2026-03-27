#include "dandan/abilities/TriggeredAbility.h"
#include <nlohmann/json.hpp>
#include <iostream>

namespace dandan::abilities
{

    void PeekEffect::apply()
    {
        std::cout << "Applying PeekEffect: peeking at the top " << m_peek_amount << " cards of the library\n";
    }

    void PeekEffect::from_json(const nlohmann::json &j, ITriggeredEffect &effect)
    {
    }

    void PeekEffect::to_json(nlohmann::json &j, const ITriggeredEffect &effect)
    {
        const auto &peekEffect = dynamic_cast<const PeekEffect &>(effect);
        j = nlohmann::json{{"type", "PeekEffect"}, {"data", nlohmann::json()}};
        j["data"]["peek_amount"] = peekEffect.m_peek_amount;
    }
}