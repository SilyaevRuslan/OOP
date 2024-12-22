#ifndef FIELDRENDERER_HPP
#define FIELDRENDERER_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

const int INDENTATION = 5;

class GameRenderer{
public:
    std::string RenderField(std::vector<std::vector<std::string>> field, bool isEnemyField);
};

#endif