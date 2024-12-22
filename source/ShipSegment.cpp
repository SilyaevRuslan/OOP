#include "ShipSegment.hpp"

ShipSegment::ShipSegment(): HP(2) {};

ShipSegment::ShipSegment(int hp) : HP(hp) {};

ShipSegment::~ShipSegment() {}

void ShipSegment::takeDamage(uint8_t damage) { 
    DamageTaken = true;
    if (HP == 0) {
        throw AttackingDestroyedSegmentException();
    }
    
    if (HP-damage>=0) {
        HP = HP-damage;
    } else {
        HP = 0;
    }
}

bool ShipSegment::isDamaged() { 
    return HP < 2;
}

bool ShipSegment::isDestroyed() {
    return HP == 0;
}