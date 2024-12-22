#ifndef SHIPSEGMENT_HPP
#define SHIPSEGMENT_HPP

#include <cstdint>
#include <Exceptions.hpp>

class ShipSegment{
public:
    explicit ShipSegment();
    ShipSegment(int hp);
    ~ShipSegment();
    void takeDamage(uint8_t damage);
    bool isDestroyed();
    bool isDamaged();
    void setHP(int hp) {
        if (hp < 0) {
            HP = 0;
        }
        HP = hp;
    };
    int getHP() const { return HP; };

private:
    uint8_t HP; 
    bool DamageTaken = false;
};

#endif