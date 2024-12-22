#include "UI.hpp"

char* colorUserStatus(CellStatus status, bool revealed){
    switch (status) {
        case CellStatus::Water:
            if (!revealed){
                return "\033[1;34m~\033[0m";
            }
            return "\033[1;31m~\033[0m";
        case CellStatus::ShipPart: return "\033[1;32mS\033[0m";
        case CellStatus::Hit: return "\033[1;33mX\033[0m";
        case CellStatus::Destroyed: return "\033[1;31mX\033[0m";
    }
}

char* colorEnemyStatus(CellStatus status, bool revealed){
    if (!revealed) return "\033[1;34m~\033[0m";
    switch (status) {
        case CellStatus::Water: return "\033[1;31m~\033[0m";
        case CellStatus::ShipPart: return "\033[1;35mS\033[0m";
        case CellStatus::Hit: return "\033[1;33mX\033[0m";
        case CellStatus::Destroyed: return "\033[1;31mX\033[0m";
    }
}

std::vector<std::vector<std::string>> CellsRenderer::RenderCells(std::vector<std::vector<FieldCell>> field, bool isEnemyField) {
    std::vector<std::vector<std::string>> res; 

    for (auto vec: field) {
        std::vector<std::string> row_chars;    
        for (auto cell: vec) {
            if (isEnemyField) {
                std::string str{colorEnemyStatus(cell.getStatus(), cell.isRevealed())};
                row_chars.push_back(str);
            } else {
                std::string str{colorUserStatus(cell.getStatus(), cell.isRevealed())};
                row_chars.push_back(str);
            }
        }
        res.push_back(row_chars);
    }

    return res;
}