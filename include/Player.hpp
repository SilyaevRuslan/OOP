#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <algorithm>
#include <random>

#include "Field.hpp"

#include "ShipManager.hpp"
#include "Result.hpp"

class Player{
public:
    Player(Field* f, ShipManager* sm, bool TakeDoubleDamage) : field(f), shipManager(sm), TakeDoubleDamage(TakeDoubleDamage){}
    ~Player() {delete shipManager; delete field;}
    
    std::vector<std::vector<FieldCell>> GetFieldCells();
    
    Result PlaceShip(Ship* ship, int x, int y, bool vertical) noexcept;
    void PlaceAllShips();
    std::vector<Ship*> GetShips();
    Result HandleAttack(int x, int y) noexcept;
    bool TakeDoubleDamage;
protected:
    Field* field;
    ShipManager* shipManager;
};

#endif