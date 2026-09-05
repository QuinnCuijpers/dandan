#ifndef DANDAN_TEST_LANDDEFINITIONS_H
#define DANDAN_TEST_LANDDEFINITIONS_H

#include "dandan/dandan.h"
#include <memory>
#include <vector>

std::vector<std::unique_ptr<dandan::IAbility>> Island_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Island_TESTS_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Remote_Isle_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Lonely_Sandbar_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Halimar_Depths_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Shivan_Reef_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Temple_of_Epiphany_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Izzet_Boilerworks_Abilities();

std::vector<std::unique_ptr<dandan::IAbility>> Svyelunite_Temple_Abilities();

#endif
