#include "Player.hpp"
#include "AbilityManager.hpp"
#include "UI.hpp"
#include "GameState.hpp"
#include "Deserializer.hpp"
#include "Serializer.hpp"

class Game {
public:
    Game();
    Game(GameState* state){
        player = state->GetPlayer();
        computer = state->GetComputer();
        abilityManager = state->GetAbilityManager();
        renderer = new CellsRenderer();
    };
    // Requires ctx to have valid x and y coordinates
    // Attacks computer and depending on outcome does smthin else
    std::string MakeTurn(Context ctx);
    std::string UseAbilityOnComputer(Context ctx);
    // Shows current available ability
    std::string PreviewNextAbility(Context ctx);
    // If context has 'owner' param and it equals player, it returns player's field
    // If 'owner' is equal to "Computer", it returns computer's field
    std::vector<std::vector<std::string>> GetField(bool isPlayerField);
    std::string Save(Context ctx);
    std::string Load(Context ctx);
private:
    void NewGame(); 
    void StartNewRound();
    Player* player;
    Player* computer;
    AbilityManager* abilityManager;
    CellsRenderer* renderer;
};