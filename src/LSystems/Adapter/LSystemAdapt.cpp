//
// Created by tibov on 08/08/24.
//

#include <fstream>
#include "LSystemAdapt.h"


template class LSystemAdapt<LParser::LSystem2D>;
template class LSystemAdapt<LParser::LSystem3D>;

template<typename T>
LSystemAdapt<T>::LSystemAdapt(const std::string &inputFile, const Color &c): color{c} {
    std::ifstream input_stream(inputFile);
    input_stream >> lSystem;
    input_stream.close();
}