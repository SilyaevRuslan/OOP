#include "Serializer.hpp"
#include <fstream>

nlohmann::json Serializer::to_json(std::vector<Ship*> ships) {
    nlohmann::json j = nlohmann::json{};

    for (int i = 0; i < ships.size(); i++) {
        Ship* temp = ships[i];
        std::string key = "ship" + std::to_string(i);
        j[key] = {
            {"x", temp->getX()},
            {"y", temp->getY()},     
            {"length", temp->getSize()},
            {"vertical", temp->isVertical()},
            {"segments", nlohmann::json::array()}
        }; 

        auto segments = temp->getSegments();
        for (int k = 0; k < segments.size(); k++) {
            auto tempSegment = segments[k];
            j[key]["segments"].push_back({
                {"health", tempSegment->getHP()},
            });
        }
    }

    return j;
}

nlohmann::json Serializer::to_json(std::vector<std::vector<FieldCell>> field) {
    nlohmann::json j = nlohmann::json{};

    for (int y = 0; y < field.size(); y++) {
        for (int x = 0; x < field[0].size(); x++) {
            std::string key = std::to_string(y) + std::to_string(x);
            j[key] = {
                {"revealed", field[y][x].isRevealed()}, 
            };
        }
    }

    return j;
}

nlohmann::json Serializer::to_json(AbilityManager* abilityManager) {
    nlohmann::json j = nlohmann::json{};
    
    for (auto type : abilityManager->GetAllAbilities()) {
        j["abilities"].push_back(
            type
        );
    }
    return j;
}

nlohmann::json Serializer::to_json(Player* player) {
    nlohmann::json j = nlohmann::json{};

    j["ships"] = to_json(player->GetShips());
    j["field"] = to_json(player->GetFieldCells());
    j["take_double_damage"] = player->TakeDoubleDamage;

    return j;
}

nlohmann::json Serializer::to_json(GameState* gameState) {
    nlohmann::json j = nlohmann::json{};

    j["player"] = to_json(gameState->GetPlayer());
    j["computer"] = to_json(gameState->GetComputer());
    j["ability_manager"] = to_json(gameState->GetAbilityManager());

    return j;
}