#ifndef ABILITIES_HPP
#define ABILITIES_HPP

#include "Player.hpp"
#include "Context.hpp"

#include <algorithm>
#include <random>
#include <ctime>

enum class AbilityType : int {
    DoubleDamage,
    Scanner,
    Bombardment,
};

// Класс-интерфейс для способности
class Ability {
public:
    virtual Result Apply(Player* player, Context ctx) = 0;
    virtual std::string Name() const = 0;
    virtual int GetType() = 0;
};

// Двойной урон
class DoubleDamage : public Ability {
public:
    Result Apply(Player* player, Context ctx) noexcept;
    std::string Name() const {return "Double Damage";};
    int GetType() {return static_cast<int>(AbilityType::DoubleDamage);};
};

// Сканер
class Scanner : public Ability {
public:
    Result Apply(Player* player, Context ctx) noexcept;
    std::string Name() const {return "Scanner";};
    int GetType() {return static_cast<int>(AbilityType::Scanner);};
};

// Обстрел
class Bombardment : public Ability {
public:
    Result Apply(Player* player, Context ctx) noexcept;
    std::string Name() const {return "Bombardment";};
    int GetType() {return static_cast<int>(AbilityType::Bombardment);};
};

#endif