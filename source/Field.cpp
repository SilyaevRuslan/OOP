#include "Field.hpp"

Field::Field(int height, int width) {
    for (int i=0; i<height; i++) {
        std::vector<FieldCell> newvector;
        for (int j=0; j<width; j++) {
            auto cell = FieldCell{};
            newvector.push_back(cell);
        }
        field.push_back(newvector);
    }
};

Field::~Field() {
    // for (auto& row : field) {
    //     for (auto& cell : row) {
    //         delete cell;
    //     }
    // }
};

std::vector<std::vector<FieldCell>> Field::getCells() {
    std::vector<std::vector<FieldCell>> result;

    for (auto& row : field) {
        std::vector<FieldCell> newvector;
        for (auto& cell : row) {
            newvector.push_back(cell);
        }
        result.push_back(newvector);
    }
    
    return result;
}

std::string Field::attackCell(int x, int y, uint8_t damage){
    if (x < 0 || y < 0 || x >= field[0].size() || y >= field.size()) {
        throw OutOfBoundsException();
    }
    
    FieldCell *cell = &field[y][x];
    
    if (cell->getStatus() == CellStatus::Water) {
        if (cell->isRevealed()) {
            throw EmptyCellAttackException();
        }   
        cell->reveal();
        return "Missed!";
    }

    cell->attackSegment(damage);
    if (cell->getStatus() == CellStatus::Destroyed) {
        return "Segment destroyed!";
    }
    return "Segment hit!";
};

bool Field::PlaceShip(Ship* ship, int horizontalPos, int verticalPos, bool vertical) {
    int size = ship->getSize();
    ship->setVertical(vertical);
    
    if (vertical) {
        if (verticalPos < 0 || verticalPos + size > field.size()) {
            return false;
        }
    } else {
        if (horizontalPos < 0 || horizontalPos + size > field[0].size()) {
            return false;
        }
    }

    int x_range, y_range;
    if (vertical) {
        x_range = 2;
        y_range = size + 1;
    } else {
        x_range = size + 1;
        y_range = 2;
    }

    for (int y=-1; y<y_range; y++) {
        for (int x=-1; x<x_range; x++){
            if (horizontalPos+x < 0 || horizontalPos+x >= field[0].size() || verticalPos+y < 0 || verticalPos+y >= field.size()) { continue; }

            if (field[verticalPos+y][horizontalPos+x].getStatus()!=CellStatus::Water) {
                return false;
            }
        }
    }

    ship->setcoords(horizontalPos, verticalPos);

    auto segments = ship->getSegments();
    for (int i=0; i<size; i++) {
        if (vertical) {
            field[verticalPos+i][horizontalPos].setShipSegment(segments[i]);
        } else {
            field[verticalPos][horizontalPos+i].setShipSegment(segments[i]);
        }
    }
    return true;
}