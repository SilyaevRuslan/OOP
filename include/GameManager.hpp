#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "FieldRenderer.hpp"
#include "Game.hpp"
#include "Command.hpp"
#include "Context.hpp"
#include "CLICommandReader.hpp"

template <class renderer, class reader>
class GameManager {
public:
    GameManager(){};
    void run() {
        game = new Game;
        gameisrunning = true;

        while (gameisrunning) {
            renderFields();
            processTurn();
        }
    }

private:
    bool gameisrunning;
    reader commandReader;
    renderer fieldRenderer;
    Game* game;
    void processTurn() {
        std::string input;
        std::string commandResult;
        while (true) {
            std::cout << "Enter command: ";
            std::getline(std::cin, input);
            if (input == "exit") {
                gameisrunning = false;
                break;
            }
            try {
                Command command = commandReader.parseCommand(input);
                Context context;
                switch(command.type){
                    case CommandType::Attack:
                        context.SetParam("x", std::to_string(command.x));
                        context.SetParam("y", std::to_string(command.y));
                        commandResult = game->MakeTurn(context);
                        
                        std::cout << commandResult << std::endl;
                        waitForEnter();
                        break;
                    case CommandType::Ability:
                        context.SetParam("x", std::to_string(command.x));
                        context.SetParam("y", std::to_string(command.y));
                        commandResult = game->UseAbilityOnComputer(context);
                        
                        std::cout << commandResult << std::endl;
                        waitForEnter();
                        break;
                    case CommandType::Load:
                        commandResult = game->Load(context);
                        
                        std::cout << commandResult << std::endl;
                        waitForEnter();
                        break;
                    case CommandType::Save:
                        commandResult = game->Save(context);
                        
                        std::cout << commandResult << std::endl;
                        waitForEnter();
                        break;
                    case CommandType::PreviewAbility:
                        commandResult = game->PreviewNextAbility(context);
                        
                        std::cout << commandResult << std::endl;
                        waitForEnter();
                        break;
                    case CommandType::Invalid:
                        std::cout << "Invalid Command" << std::endl;
                        break;
                }
                break;
            } catch (const InvalidCommandException& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    void renderFields() {
        std::vector<std::vector<std::string>> playerField = game->GetField(true);
        std::vector<std::vector<std::string>> enemyField = game->GetField(false);
        std::cout << fieldRenderer.RenderField(playerField, false) << std::endl;
        std::cout << fieldRenderer.RenderField(enemyField, true) << std::endl;
    }
    
    void waitForEnter(){
        std::cout << "Press Enter to continue..." << std::endl;
        std::cin.get();
        system("clear");
    }
};

#endif