#include "Ship.hpp"


Ship::Ship(int size) {
    if (size < 1 || size > 4) {
        std::__throw_invalid_argument("ship's size must be between 1 and 4");
    }
    
    for (int i = 0; i < size; i++) {
        auto segment = new ShipSegment;
        segments.push_back(segment);
    }
}

Ship::~Ship() {
    for (auto segment : segments) {
        delete segment;
    }
    segments.clear();
}

int Ship::getSize() const { return segments.size(); }

std::vector<ShipSegment*> Ship::getSegments() const {
    return segments;
}

bool Ship::isDestroyed() const {
    for (auto segment : segments) {
        if (!segment->isDestroyed()) {
            return false;
        }
    }
    return true;
}
