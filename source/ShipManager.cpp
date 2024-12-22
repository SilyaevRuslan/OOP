#include "ShipManager.hpp"
#include <iostream>

ShipManager::ShipManager(int amount, std::vector<int> sizes) {
    for (auto size: sizes) {
        auto ship = new Ship(size);
        ships.push_back(ship);
    }

    AliveCnt = countAliveShips();
}

ShipManager::~ShipManager() {
    for (auto ship : ships) {
        delete ship;
    }
}

ShipManager::ShipManager(const ShipManager& other) {
    for (const auto& ship : other.ships) {
        auto newShip = new Ship(*ship);
        ships.push_back(newShip);
    }
    AliveCnt = other.AliveCnt;
}

ShipManager::ShipManager(ShipManager&& other) noexcept {
    ships = std::move(other.ships);
    AliveCnt = other.AliveCnt;
    other.AliveCnt = 0;
}

ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) {
        for (auto& ship : ships) {
            delete ship;
        }
        ships.clear();
        for (const auto& ship : other.ships) {
            auto newShip = new Ship(*ship);
            ships.push_back(newShip);
        }
        AliveCnt = other.AliveCnt;
    }
    return *this;
}

ShipManager& ShipManager::operator=(ShipManager&& other) noexcept {
    if (this != &other) {
        for (auto& ship : ships) {
            delete ship;
        }
        ships = std::move(other.ships);
        AliveCnt = other.AliveCnt;
        other.AliveCnt = 0;
    }
    return *this;
}

std::vector<Ship*> ShipManager::getShips() const {
    return ships;
}

int ShipManager::countAliveShips() const {
    int alive = 0;
    for (auto ship : ships) {
        if (!ship->isDestroyed()) {
            alive++;
        }
    }
    return alive;
}

