#ifndef ABILITYFACTORY_HPP
#define ABILITYFACTORY_HPP

#include "Abilities.hpp"

class AbilityFactory {
public:
    virtual Ability* createAbility(const AbilityType type) = 0;
};

class Factory : public AbilityFactory{
public:
    Factory(){};
    Ability* createAbility(const AbilityType type) {
        switch (type) {
            case AbilityType::DoubleDamage:
                return new DoubleDamage;
            case AbilityType::Scanner:
                return new Scanner;
            case AbilityType::Bombardment:
                return new Bombardment;
            default:
                throw std::invalid_argument("Invalid ability type");
        }
    }
};

#endif