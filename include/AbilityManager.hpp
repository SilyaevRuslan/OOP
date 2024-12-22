#ifndef ABILITYMANAGER_HPP
#define ABILITYMANAGER_HPP

#include <iostream>
#include <random>
#include <queue>

#include "Abilities.hpp"
#include "AbilityFactory.hpp"


class AbilityManager {
public:
    AbilityManager(AbilityFactory* factory);

    std::string previewNextAbility() const;
    void addRandom();
    void addAbility(AbilityType);
    void addAbility(int);
    Ability* GetAblity();
    std::vector<int> GetAllAbilities();
    void RemoveAbilityAtStart();
private:
    AbilityFactory* factory;
    std::queue<Ability*> abilities;
};

#endif