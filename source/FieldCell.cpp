#include "FieldCell.hpp"

FieldCell::FieldCell() : status(CellStatus::Water), revealed(false), shipSegment(nullptr) {}

CellStatus FieldCell::getStatus() {
    if (shipSegment == nullptr) {
        return CellStatus::Water;
    }
    if (shipSegment->isDestroyed()) {
        return CellStatus::Destroyed;
    }
    if (shipSegment->isDamaged()) {
        return CellStatus::Hit;
    }
    return CellStatus::ShipPart;
}

void FieldCell::reveal() {
    revealed = true;
}

bool FieldCell::isRevealed() {
    return revealed;
}

void FieldCell::attackSegment(uint8_t damage) {
    revealed = true;
    if (shipSegment == nullptr) {
        return;
    }

    shipSegment->takeDamage(damage);
}

bool FieldCell::setShipSegment(ShipSegment* segment) {
    if (shipSegment != nullptr) {
        return false;
    }

    shipSegment = segment;
    status = CellStatus::ShipPart;
    return true;
}
