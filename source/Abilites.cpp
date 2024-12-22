#include "Abilities.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Result DoubleDamage::Apply(Player* player, Context ctx) noexcept {
    player->TakeDoubleDamage = true;
    return Result{"Double damage applied", true, false, 0, false};
};

Result Scanner::Apply(Player* player, Context ctx) noexcept {
    int x, y;
    
    try {
        x = std::stoi(ctx.GetParam("x"));
        y = std::stoi(ctx.GetParam("y"));
    } catch (const std::exception &e) {
        return Result{"Invalid scanner coordinates", false, false, 0, false};
    }

    auto field = player->GetFieldCells();
    for (int i = y; i <= y + 1; i++) {
        for (int j = x; j <= x + 1; j++) {
            if (j < 0 || i < 0 || i >= field.size() || j >= field[0].size()) {
                return Result{"Scanner out of bounds", false, false, 0, false};
            }

            if (field[i][j].getStatus() != CellStatus::Water && field[i][j].getStatus() != CellStatus::Destroyed)  {
                return Result{"Scanner detected a ship", true, false, 0, false};
            }
        }
    }

    return Result{"No ship detected", true, false, 0, false};
};

Result Bombardment::Apply(Player* player, Context ctx) noexcept {
    std::vector<Ship*> ships = player->GetShips();
    std::vector<Ship*> AliveShips;

    for (auto ship : ships) {
        if (!ship->isDestroyed()) {
            AliveShips.push_back(ship);
        }
    }

    if (AliveShips.empty()) {
        return Result{"All ships are dead", false, true, 0, false};
    }

    Ship* randomShip = AliveShips[rand()%AliveShips.size()];
    ShipSegment* randomSegment = randomShip->getSegments()[rand()%randomShip->getSize()];
    randomSegment->takeDamage(1);
    return Result{"Bombardment hit a segment!", true, false, 0, true};
}

