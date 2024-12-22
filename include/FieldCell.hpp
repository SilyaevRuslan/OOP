#ifndef FIELDCELL_HPP
#define FIELDCELL_HPP

#include <cstdint>
#include <string>
#include "ShipSegment.hpp"

enum class CellStatus : char {
    Water = '~',
    ShipPart = 'S',
    Hit = 'X',  
    Destroyed = '0'
};

class FieldCell {
public:
    // Конструктор ячейки поля
    FieldCell();
    // Методы для взаимодействия с ячейкой
    CellStatus getStatus();
    void reveal();  // Метод для открытия ячейки
    bool isRevealed();
    void attackSegment(uint8_t damage);
    // Returns true if ship segment was placed successfully. False otherwise
    bool setShipSegment(ShipSegment* segment);

private:
    ShipSegment* shipSegment; // Указатель на сегмент корабля, если он есть в ячейке
    CellStatus status; // Статус клетки в виде символа
    bool revealed; // Флаг, указывающий, была ли ячейка открыта
};

#endif 