#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "AbilityManager.hpp"
#include "Player.hpp"

#include <fstream>

class GameState {
    private:
        Player* player;
        Player* computer;
        AbilityManager* manager;
    public:
        GameState(Player* player, Player* computer, AbilityManager* manager) : player(player), computer(computer), manager(manager) {};

        Player* GetPlayer() { return player; };
        Player* GetComputer() { return computer; };
        AbilityManager* GetAbilityManager() { return manager; };
};

#endif