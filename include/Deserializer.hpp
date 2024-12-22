#ifndef DESERIALIZER_HPP
#define DESERIALIZER_HPP

#include <GameState.hpp>
#include "nlohmann/json.hpp"
#include <fstream>

class Deserializer {
public:
    Deserializer() {};
    GameState* from_json_game_state(const nlohmann::json& j);

private:
    std::vector<Ship*> from_json_ships(const nlohmann::json& j);

    std::vector<std::vector<FieldCell>> from_json_field(const nlohmann::json& j);

    AbilityManager* from_json_ability_manager(const nlohmann::json& j);

    Player* from_json_player(const nlohmann::json& j);
};

#endif