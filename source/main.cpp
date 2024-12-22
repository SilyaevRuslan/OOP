#include "GameManager.hpp"
#include "FieldRenderer.hpp"

int main() {
    std::srand(std::time(nullptr)); 

    GameManager<GameRenderer, CLICommandReader> gameManager;
    gameManager.run();
    return 0;
}