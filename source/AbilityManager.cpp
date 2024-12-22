#include "AbilityManager.hpp"

AbilityManager::AbilityManager(AbilityFactory* factory) :factory(factory){};

std::string AbilityManager::previewNextAbility() const {
    if (!abilities.empty()) {
        return abilities.front()->Name();
    }
    return "No more abilities available.";

}

void AbilityManager::addRandom() {
    AbilityType randomAbility = static_cast<AbilityType>(std::rand()%3);
    addAbility(randomAbility);
}

void AbilityManager::addAbility(AbilityType type){
    Ability* newAbility = factory->createAbility(type); 

    abilities.push(newAbility);
};

void AbilityManager::addAbility(int type){
    Ability* newAbility = factory->createAbility(static_cast<AbilityType>(type)); 

    abilities.push(newAbility);
};

Ability* AbilityManager::GetAblity() {
    if (!abilities.empty()) {
        Ability* ability = abilities.front();
        return ability;
    }
    throw NoAbilitiesException();
};

void AbilityManager::RemoveAbilityAtStart() {
    try {
        abilities.pop();
    } catch (const std::exception &e) {
        throw NoAbilitiesException();
    }
}

std::vector<int> AbilityManager::GetAllAbilities() {
    std::vector<int> abilitiesVec;
    while (!abilities.empty()) {
        abilitiesVec.push_back(static_cast<int>(abilities.front()->GetType()));
        abilities.pop();
    }
    return abilitiesVec;
}