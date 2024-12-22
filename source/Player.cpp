#include "Player.hpp"

std::vector<std::vector<FieldCell>> Player::GetFieldCells() {
    return field->getCells();
};


std::vector<Ship*> Player::GetShips() {
    return shipManager->getShips();
};

Result Player::HandleAttack(int x, int y) noexcept {
    std::string message;
    int aliveShips;
    int updatedLiveShips;
    
    uint8_t damage = 1;
    if (TakeDoubleDamage) {
        damage = 2;
        TakeDoubleDamage = false;
    }

    aliveShips = shipManager->countAliveShips();

    try {
        message = field->attackCell(x, y, damage);
    } catch (std::exception& e) {
        return Result{e.what(), false, false, false, false};
    }

    updatedLiveShips = shipManager->countAliveShips();

    bool hit = message == "Segment destroyed!" || message == "Segment hit!";

    return Result{message, true, shipManager->countAliveShips()==0, aliveShips - updatedLiveShips, hit};
};

Result Player::PlaceShip(Ship* ship, int x, int y, bool vertical) noexcept {
    bool ok = field->PlaceShip(ship, x, y, vertical);
    if (ok) {
        return {"Ship placed successfully", true, false, 0, false};
    }
    return Result{"Failed to place ship", false, false, 0, false};

}

void Player::PlaceAllShips(){
    std::vector<Ship*> ships = shipManager->getShips();
    int x, y;
    bool vertical;
    int i = 0;
    while (i < ships.size()) {
        x = rand() % (field->GetWidth());
        y = rand() % (field->GetHeight());
        vertical = rand() % 2 == 0;
        bool ok = field->PlaceShip(ships[i], x, y, vertical);
        if (ok) {
            i++;
        }
    }
}