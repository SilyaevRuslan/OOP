#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>

#include "FieldCell.hpp"
#include "Ship.hpp"
#include "Exceptions.hpp"

class Field {
public:
    Field(int height, int width);
    Field(std::vector<std::vector<FieldCell>> field) : field(field) {};

    ~Field();
    std::vector<std::vector<FieldCell>> getCells();
    std::string attackCell(int x, int y, uint8_t damage);
    // Returns true if ship was placed successfully, false otherwise
    bool PlaceShip(Ship* ship, int horizontalPos, int verticalPosition, bool vertical);
    int GetWidth() const { return field[0].size(); };
    int GetHeight() const { return field.size(); };
    std::vector<std::vector<std::string>> RenderCells(std::vector<std::vector<FieldCell>> field, bool isEnemyField);
private:
    std::vector<std::vector<FieldCell>> field;
};

#endif