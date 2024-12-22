#ifndef SHIP_HPP
#define SHIP_HPP

#include <vector>
#include <memory>
#include "ShipSegment.hpp"

class Ship{
public:
    Ship(int size);
    Ship(std::vector<ShipSegment*> segments, int X, int Y, bool vertical) : segments(segments), size(segments.size()), coordx(X), coordy(Y), vertical(vertical) {};

    ~Ship();

    bool isDestroyed() const;
    int getSize() const;
    void setcoords(int x, int y ){
        coordx = x;
        coordy = y;
    };
    void setVertical(bool v) {this->vertical = v;};
    void setX(int x) {
        coordx = x;
    }
    void setY(int y) {
        coordy = y;
    }

    int getX() const { return coordx; }
    int getY() const { return coordy; }
    bool isVertical() const { return vertical; }
    std::vector<ShipSegment*> getSegments() const;
private:
    int coordx;
    int coordy;
    bool vertical;
    std::vector<ShipSegment*> segments;
    uint8_t size;
};

#endif