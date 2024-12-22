#include "FieldRenderer.hpp"

std::string GameRenderer::RenderField(std::vector<std::vector<std::string>> field, bool isEnemyField) {
    std::stringstream ss;
    
    if (isEnemyField) {    
        ss << "\033[1;31m" << std::setw(field[0].size() + INDENTATION*2 + 3) << "ENEMY FIELD" << "\033[0m\n";
    } else {
        ss << "\033[1;32m" << std::setw(field[0].size() + INDENTATION*2 + 2) << "YOUR FIELD" << "\033[0m\n";
    }
    
    ss << "        ";
    char column = '0';
    for (int i = 0; i < field[0].size();i++) {
        ss << column << " ";
        column++;
    } 
    ss << std::endl;
    
    
    ss << "      +";
    for (int i = 0; i < field[0].size();i++) { 
        ss << "——";
    } 
    ss << "—+\n";
    
    int row = 0;
    for (auto vec: field) {     
        ss << std::setw(INDENTATION) <<row<< " | ";
        for (auto cell: vec) {
            ss << cell << " ";
        }
        ss << "|\n";
        row++;
    }
    
    ss << "      +";
    for (int i = 0; i < field[0].size();i++) {
        ss << "——";
    } 
    
    ss << "—+\n";
    
    return ss.str();
}