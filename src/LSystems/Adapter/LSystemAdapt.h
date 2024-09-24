//
// Created by tibov on 08/08/24.
//

#ifndef ENGINE_LSYSTEMADAPT_H
#define ENGINE_LSYSTEMADAPT_H

#include "string"
#include "../../../libraries/l_parser.h"
#include "../../Figure/Color.h"

template <typename T>
class LSystemAdapt {


protected:
    explicit LSystemAdapt(const std::string& inputFile, const Color &c);

    T lSystem;
    Color color{};


};




#endif //ENGINE_LSYSTEMADAPT_H
