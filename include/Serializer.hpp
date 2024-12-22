#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <string.h>
#include <nlohmann/json.hpp>

#include "Player.hpp"
#include "GameState.hpp"
#include "AbilityManager.hpp"

class Serializer {
public:
    Serializer(){};
    nlohmann::json to_json(GameState* gameState);
private:
    nlohmann::json to_json(std::vector<Ship*> ships);
    nlohmann::json to_json(std::vector<std::vector<FieldCell>> field);
    nlohmann::json to_json(AbilityManager* abilityManager);
    nlohmann::json to_json(Player* player);
};

#endif  SERIALIZER_HPP