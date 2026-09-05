#ifndef DANDAN_SPELL_DEFINITIONS_H
#define DANDAN_SPELL_DEFINITIONS_H

#include "dandan/abilities/IAbility.h"
#include <memory>

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Brainstorm_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Accumulated_Knowledge_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Diminishing_Returns_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Mystical_Tutor_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Vision_Charm_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Crystal_Spray_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>> Mind_Bend_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Unsubstantiate_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Memory_Lapse_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>> Predict_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Dance_of_the_Skywise_Abilities();

std::vector<std::unique_ptr<dandan::abilities::IAbility>>
Metamorphose_Abilities();

#endif
