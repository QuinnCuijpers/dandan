#include "dandan/ManaAbility.h"
#include <nlohmann/json.hpp>

void ManaAbility::resolve()
{
    std::cout << "Resolving ManaAbility: " << ManaTypeToString(m_color) << " mana\n";
}

NLOHMANN_JSON_SERIALIZE_ENUM(ManaAbility::ManaType, {{ManaAbility::ManaType::COLORLESS, "Colorless"},
                                                     {ManaAbility::ManaType::WHITE, "White"},
                                                     {ManaAbility::ManaType::BLUE, "Blue"},
                                                     {ManaAbility::ManaType::BLACK, "Black"},
                                                     {ManaAbility::ManaType::RED, "Red"},
                                                     {ManaAbility::ManaType::GREEN, "Green"}})

void ManaAbility::from_json(const nlohmann::json &j, IAbility &ability)
{
    auto &manaAbility = dynamic_cast<ManaAbility &>(ability);
    manaAbility.m_color = j.at("color").get<ManaAbility::ManaType>();
}

void ManaAbility::to_json(nlohmann::json &j, const IAbility &ability)
{
    j = nlohmann::json{{"ManaAbility", nlohmann::json()}};
    j["ManaAbility"]["color"] = ManaTypeToString(m_color);
}