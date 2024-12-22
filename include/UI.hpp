#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "FieldCell.hpp"

class CellsRenderer{
public:
    std::vector<std::vector<std::string>> RenderCells(std::vector<std::vector<FieldCell>> field, bool isEnemyField);
    std::string RenderField(std::vector<std::vector<std::string>> field, bool isEnemyField);
};

#endif