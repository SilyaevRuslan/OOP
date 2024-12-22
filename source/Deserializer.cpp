#include "Deserializer.hpp"

std::vector<Ship*> Deserializer::from_json_ships(const nlohmann::json& j) {
    std::vector<Ship*> ships;
    for (auto& [key, value] : j.items()) {
        int x = value["x"];
        int y = value["y"];
        bool vertical = value["vertical"];        
        
        std::vector<ShipSegment*> segments;
        for (auto& segment : value["segments"]) {
            int health = segment["health"];
            ShipSegment* s = new ShipSegment(health);
            segments.push_back(s);
        }

        Ship* ship = new Ship(segments, x, y, vertical);
        ships.push_back(ship);
    }
    return ships;
}
std::vector<std::vector<FieldCell>> Deserializer::from_json_field(const nlohmann::json& j) {
    std::vector<std::vector<FieldCell>> field;
    for (int y = 0; y < 10; y++) {
        std::vector<FieldCell> row;
        for (int x = 0; x < 10; x++) {
            std::string key = std::to_string(y) + std::to_string(x);
            bool revealed = j[key]["revealed"];
            FieldCell cell;
            if (revealed) {
                cell.reveal();
            }
            row.push_back(cell);
        }
        field.push_back(row);
    }
    return field;
}

AbilityManager* Deserializer::from_json_ability_manager(const nlohmann::json& j) {
    Factory* f = new Factory();
    AbilityManager* abilityManager = new AbilityManager(f);
    
    try {
        for (int ability : j["abilities"]) {
            abilityManager->addAbility(ability);
        }
    } catch (const std::exception& e) {
    }
    
    return abilityManager;
}

Player* Deserializer::from_json_player(const nlohmann::json& j) {
    Field* field = new Field(from_json_field(j["field"]));
    ShipManager* sm = new ShipManager(from_json_ships(j["ships"]));
    bool tdd = j["take_double_damage"];

    auto ships = sm->getShips();
    for (auto ship : ships) {
        int x = ship->getX();
        int y = ship->getY();
        bool vertical = ship->isVertical();
        field->PlaceShip(ship, x, y, vertical);
    }

    Player* player = new Player(field, sm, tdd);
    return player;
}

GameState* Deserializer::from_json_game_state(const nlohmann::json& j) {
    Player* p = from_json_player(j["player"]);
    Player* c = from_json_player(j["computer"]);
    AbilityManager* am = from_json_ability_manager(j["ability_manager"]);

    GameState* gameState = new GameState(p, c, am);
    return gameState;
}