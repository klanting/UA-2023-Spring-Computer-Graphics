//
// Created by tibov on 08/08/24.
//

#include <fstream>
#include "LSystemAdapt.h"


template class LSystemAdapt<LParser::LSystem2D>;
template class LSystemAdapt<LParser::LSystem3D>;

template<typename T>
LSystemAdapt<T>::LSystemAdapt(const std::string &input_file) {
    std::ifstream input_stream(input_file);
    input_stream >> l_system;
    input_stream.close();
}