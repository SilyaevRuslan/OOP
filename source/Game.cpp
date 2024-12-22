#include "Game.hpp"

Game::Game() {
    NewGame();
}

std::string Game::MakeTurn(Context ctx) {
    std::stringstream ss;
    int x, y;
    // Player attacks
    try {
        x = std::stoi(ctx.GetParam("x"));
        y = std::stoi(ctx.GetParam("y"));
    } catch (std::exception& e) {
        return "Invalid coordinates";
    }
    
    Result result = computer->HandleAttack(x, y);
    ss << result.Message() << std::endl;
    // if attack wasn't valid, computer doesn't do anything
    if (!result.Success()) {
        return ss.str();
    }

    // if all computer ships are destroyed
    if (result.AllShipsDestroyed()) {
        StartNewRound();
        ss << "Player wins!" << std::endl;
        return ss.str();
    }

    // Add random ability, if ship was destroyed;
    for (int i = 0; i < result.ShipsDestroyed(); i++) {
        abilityManager->addRandom();
        ss << "New ability acquired" << std::endl;
    }

    if (result.Hit()) {
        return ss.str();
    }

    // Bot's turn 
    ss << "Bot's turn" << std::endl;

    while (true) {
        int x = rand() % (computer->GetFieldCells()[0].size());
        int y = rand() % (computer->GetFieldCells().size());
        result = player->HandleAttack(x, y);

        // if attack was valid, leave this stupid cycle
        if (result.Success()) {
            ss << result.Message() << std::endl;
            if (!result.Hit()) {
                break;
            }
        }
    }

    // if all player ships are destroyed
    
    if (result.AllShipsDestroyed()) {
        Game();
        NewGame();
        ss << "Computer wins!" << std::endl;
        return ss.str();
    }

    if (result.ShipsDestroyed() > 0) {
        ss << "Computer destroyed a ship!" << std::endl;
    }
    return ss.str();
};

std::string Game::UseAbilityOnComputer(Context ctx) {
    Ability* ability;
    try {
        ability = abilityManager->GetAblity();
    } catch (NoAbilitiesException& e) {
        return e.what();
    }
    Result result = ability->Apply(computer, ctx);
    
    if (result.Success()) {
        try {
            abilityManager->RemoveAbilityAtStart();
        } catch (NoAbilitiesException& e) {
            return e.what();
        }
    }
    
    // Add random ability, if ship was destroyed;
    for (int i = 0; i < result.ShipsDestroyed(); i++) {
        abilityManager->addRandom();
    }

    return result.Message();
}

std::string Game::PreviewNextAbility(Context ctx) {
    return abilityManager->previewNextAbility();
}

std::vector<std::vector<std::string>> Game::GetField(bool isPlayerField){
    if (isPlayerField) {
        return renderer->RenderCells(player->GetFieldCells(), false);
    }
    return renderer->RenderCells(computer->GetFieldCells(), true);
}

void Game::NewGame() {
    // initialize player
    Field* field = new Field(10, 10);
    ShipManager* playerManager = new ShipManager(7, std::vector<int>({4, 3, 3, 2, 2, 2, 1, 1, 1, 1}));
    player = new Player(field, playerManager, false);
    player->PlaceAllShips();

    // initialize computer
    Field* computerField = new Field(10, 10);
    ShipManager* computerManager = new ShipManager(7, std::vector<int>({4, 3, 3, 2, 2, 2, 1, 1, 1, 1}));
    computer = new Player(computerField, computerManager, false);
    computer->PlaceAllShips();

    // initialize ability manager
    Factory* factory = new Factory();
    abilityManager = new AbilityManager(factory);

    std::vector<int> vec;
    for (int i = 0; i < 3; i++){
        vec.push_back(i);  
    }
    std::random_shuffle(vec.begin(), vec.end());  
    for (int ability: vec) {
        abilityManager->addAbility(ability);
    }
    
    // // initialize field renderer
    renderer = new CellsRenderer();
}

void Game::StartNewRound() {
    // Reset double damage flag
    computer->TakeDoubleDamage=false;

    // Ressurect computer
    Field* computerField = new Field(10, 10);
    ShipManager* computerManager = new ShipManager(7, std::vector<int>({4, 3, 3, 2, 2, 2, 1}));
    computer = new Player(computerField, computerManager, false);
    computer->PlaceAllShips();
}

std::string Game::Save(Context ctx) {
    GameState* state = new GameState(player, computer, abilityManager);
    Serializer serializer;

    nlohmann::json j = serializer.to_json(state);

    std::ofstream file("save.json");
    file << j.dump(4) << std::endl;
    file.close();

    Load(ctx);
    
    return "Game saved successfully";
}

std::string Game::Load(Context ctx) {
    nlohmann::json j;
    std::ifstream file2("save.json");
    if (file2.is_open()) {
        file2 >> j;
        file2.close();
    } else {
        return "Save file not found";
    }

    Deserializer d{};
    GameState* state = d.from_json_game_state(j);

    player = state->GetPlayer();
    computer = state->GetComputer();
    abilityManager = state->GetAbilityManager();

    return "Game loaded successfully";
}